// 文字コード：UTF-8
#include <ae/base/Display.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Display::Display(const DisplayContext& aContext)
: mContext(aContext)
, mExt(aContext)
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
const DisplayContext Display::context_()const
{
    return mContext;
}

//------------------------------------------------------------------------------
Display_Ext& Display::ext_()
{
    return mExt;
}

}} // namespace
// EOF
