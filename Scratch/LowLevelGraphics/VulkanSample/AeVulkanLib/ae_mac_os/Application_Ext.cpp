// 文字コード：UTF-8
#include <ae/base/Application.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/Hid.hpp>
#include <ae/base/Thread.hpp>
#include <ae/base/Time.hpp>
#include <ae/base/TimeSpan.hpp>

#include "AeBaseNSApp.h"

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
void Application::Quit() {
    // フラグを立てる
    ext_.doQuit = true;

    // 終了処理
    AeBaseNSApp_Terminate();
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::ReceiveEventCore() {
    // Hidのフラグをおろしておく
    if (displayPtr_.IsValid()) {
        displayPtr_->Ext_().keyboardUpdateData.pulse.Clear();
        displayPtr_->Ext_().mouseUpdateData.posUpdated = false;
    }

    // イベント処理
    AeBaseNSApp_PollEvent();

    // 終了要求が来たら終了
    if (ext_.doQuit) {
        return AppEvent::Quit;
    }

    // Hid更新
    if (displayPtr_.IsValid() && displayPtr_->Ext_().hidPtr.IsValid()) {
        // 更新の前の設定
        if (displayPtr_->Ext_().mouseUpdateData.hold.IsAnyOn()) {
            displayPtr_->Ext_().mouseUpdateData.posUpdated = true;
        }

        // 更新
        Hid_Ext& hidExt = displayPtr_->Ext_().hidPtr->Ext_();
        hidExt.keyboard.Update(displayPtr_->Ext_().keyboardUpdateData);
        hidExt.mouse.Update(displayPtr_->Ext_().mouseUpdateData);
    }

    { // 60フレ同期
        s64 currentTicks = s64();
        while (true) {
            currentTicks = Time::LocalTime().Ticks();
            if ((currentTicks - ext_.prevUpdateTicks) < 166666) {
                Thread::Sleep(TimeSpan::FromMilliseconds(1));
                continue;
            }
            break;
        }
        ext_.prevUpdateTicks = currentTicks;
    }

    // 通常は更新
    return AppEvent::Update;
}

//------------------------------------------------------------------------------
Application_Ext::Application_Ext()
: prevUpdateTicks(Time::LocalTime().Ticks())
, doQuit(false) {
    AeBaseNSApp_Initialize();
}

//------------------------------------------------------------------------------
Application_Ext::~Application_Ext() {
    AeBaseNSApp_Finalize();
}

} // namespace base
} // namespace ae
// EOF
