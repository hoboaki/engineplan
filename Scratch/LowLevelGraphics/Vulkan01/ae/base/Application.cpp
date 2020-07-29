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
    return tPtr.ref();
}

//------------------------------------------------------------------------------
ae::base::Application::Application(const Argument& aArgument)
: argument_(aArgument)
, lastEvent_(AppEvent::INVALID)
, displayPtr_()
, ext_()
{
    tPtr.set(*this);
}

//------------------------------------------------------------------------------
Application::~Application()
{
    tPtr.unset();
}

//------------------------------------------------------------------------------
const Argument& Application::argument()const
{
    return argument_;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::receiveEvent()
{
    lastEvent_ = receiveEventCore();
    return lastEvent_;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::lastEvent()const
{
    return lastEvent_;
}

//------------------------------------------------------------------------------
void Application::registerDisplay_(Display& aDisplay)
{
    displayPtr_.set(aDisplay);
}

//------------------------------------------------------------------------------
void Application::unregisterDisplay_(Display& aDisplay)
{
    displayPtr_.unset(aDisplay);
}

}} // namespace
// EOF
