// 文字コード：UTF-8
#include <ae/base/Application.hpp>

#include <ae/base/Display.hpp>
#include <ae/base/Thread.hpp>
#include <ae/base/TimeSpan.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

u64 tCurrentUSec()
{
    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq) == TRUE) {
        LARGE_INTEGER time;
        QueryPerformanceCounter(&time);
        return time.QuadPart / (freq.QuadPart / (1000 * 1000));
    }
    else
    {
        return Time::LocalTime().ticks() / 10;
    }
}

} // namespace

//------------------------------------------------------------------------------
void Application::quit()
{
    ext_.doQuit = true;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::receiveEventCore()
{
    // 終了要求があったらQuit
    if (ext_.doQuit) {
        return AppEvent::Quit;
    }
    // ディスプレイのイベントチェック
    if (displayPtr_.isValid()) {
        displayPtr_->Ext_().pollEvent(*this);
    }

    // 60フレ同期
    {
        u64 currentUSec = u64();
        while (true) {
            currentUSec = tCurrentUSec();
            if (ext_.prevUSec <= currentUSec) {// オーバーフローしていることもあるので。
                if (currentUSec - ext_.prevUSec < 16666) {
                    Thread::Sleep(TimeSpan::FromMilliseconds(1));
                    continue;
                }
            }
            break;
        }
        ext_.prevUSec = currentUSec;
    }

    // 常にUpdate
    return AppEvent::Update;
}

//------------------------------------------------------------------------------
Application_Ext::Application_Ext()
: prevUSec(tCurrentUSec())
, doQuit(false)
{
}

}} // namespace
// EOF
