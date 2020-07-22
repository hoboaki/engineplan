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
: mArgument(aArgument)
, mLastEvent(AppEvent::INVALID)
, mDisplayPtr()
, mExt()
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
    return mArgument;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::receiveEvent()
{
    mLastEvent = receiveEventCore();
    return mLastEvent;
}

//------------------------------------------------------------------------------
AppEvent::EnumType Application::lastEvent()const
{
    return mLastEvent;
}

//------------------------------------------------------------------------------
void Application::registerDisplay_(Display& aDisplay)
{
    mDisplayPtr.set(aDisplay);
}

//------------------------------------------------------------------------------
void Application::unregisterDisplay_(Display& aDisplay)
{
    mDisplayPtr.unset(aDisplay);
}

}} // namespace
// EOF
