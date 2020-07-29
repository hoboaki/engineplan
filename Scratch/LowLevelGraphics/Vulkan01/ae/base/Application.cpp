// 文字コード：UTF-8
#include <ae/base/Application.hpp>

#include <ae/base/Display.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {
//------------------------------------------------------------------------------
namespace {

Pointer< Application > tPtr;
}
//------------------------------------------------------------------------------
Application& Application::Instance()
{
    return tPtr.Ref();
}

//------------------------------------------------------------------------------
ae::base::Application::Application(const base::Argument& aArgument)
: argument_(aArgument)
, lastEvent_(AppEvent::INVALID)
, displayPtr_()
, ext_()
{
    tPtr.Set(*this);
}

//------------------------------------------------------------------------------
Application::~Application()
{
    tPtr.Unset();
}

//------------------------------------------------------------------------------
const Argument& Application::Argument()const
{
    return argument_;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::ReceiveEvent()
{
    lastEvent_ = ReceiveEventCore();
    return lastEvent_;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::LastEvent()const
{
    return lastEvent_;
}

//------------------------------------------------------------------------------
void Application::registerDisplay_(Display& aDisplay)
{
    displayPtr_.Set(aDisplay);
}

//------------------------------------------------------------------------------
void Application::unregisterDisplay_(Display& aDisplay)
{
    displayPtr_.Unset(aDisplay);
}

}} // namespace
// EOF
