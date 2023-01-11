// 文字コード：UTF-8
#include <ae/base/Display.hpp>

// includes
#include <ae/base/Application.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Display::Display(const DisplayContext& context)
: context_(context)
, ext_(context)
{
    // 登録
    Application::Instance().registerDisplay_(*this);
}

//------------------------------------------------------------------------------
Display::~Display()
{
    // 登録解除
    Application::Instance().unregisterDisplay_(*this);
}

//------------------------------------------------------------------------------
const DisplayContext Display::Context_() const
{
    return context_;
}

//------------------------------------------------------------------------------
Display_Ext& Display::Ext_()
{
    return ext_;
}

} // namespace ae::base
// EOF
