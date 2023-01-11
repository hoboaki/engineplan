// 文字コード：UTF-8
#include <ae/base/Application.hpp>

// includes
#include <ae/base/Display.hpp>

//------------------------------------------------------------------------------
namespace ae::base {
//------------------------------------------------------------------------------
namespace {

Pointer<Application> tPtr;
}
//------------------------------------------------------------------------------
Application& Application::Instance()
{
    return tPtr.Ref();
}

//------------------------------------------------------------------------------
ae::base::Application::Application(const base::Argument& argument)
: argument_(argument)
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
const Argument& Application::Argument() const
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
AppEvent::EnumType Application::LastEvent() const
{
    return lastEvent_;
}

//------------------------------------------------------------------------------
void Application::registerDisplay_(Display& display)
{
    displayPtr_.Set(display);
}

//------------------------------------------------------------------------------
void Application::unregisterDisplay_(Display& display)
{
    displayPtr_.Unset(display);
}

} // namespace ae::base
// EOF
