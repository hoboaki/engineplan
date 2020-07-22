// 文字コード：UTF-8
#include <ae/base/DisplayContext.hpp>

#include <ae/base/SdkHeader.hpp>

#if defined(AE_BASE_OS_MACOSX)
    #include <ae_mac_os/AeBaseNSScreen.h>
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {
#if defined(AE_BASE_OSTYPE_WINDOWSYSTEM)

//------------------------------------------------------------------------------
namespace {

enum
{
    tDefaultWidth = 1280,
    tDefaultHeight = 720
};

}

//------------------------------------------------------------------------------
DisplayContext::DisplayContext()
: mLocationX(0)
, mLocationY(0)
, mWidth(tDefaultWidth)
, mHeight(tDefaultHeight)
, mIsScreenDoubleBuffer(true)
{
    // センタリング
    setLocationToCenter();
}

//------------------------------------------------------------------------------
void DisplayContext::setLocationToCenter()
{
#if defined(AE_BASE_OS_WINDOWS)
    // 情報取得
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    const int dispWidth = GetDeviceCaps(hdc, HORZRES);
    const int dispHeight = GetDeviceCaps(hdc, VERTRES);
    ReleaseDC(hwnd, hdc);

    // 位置設定
    if (mWidth < dispWidth) {
        mLocationX = (dispWidth - mWidth) / 2;
    }
    if (mHeight < dispHeight) {
        mLocationY = (dispHeight - mHeight) / 2;
    }
#elif defined(AE_BASE_OS_MACOSX)
    // 情報取得
    AeBaseNSRect rect = {};
    AeBaseNSScreen_GetMainScreenVisibleFrame(&rect);

    // 位置設定
    if (mWidth < rect.sizeW) {
        mLocationX = uint(rect.originX + (rect.sizeW - mWidth) / 2);
    }
    if (mHeight < rect.sizeH) {
        mLocationY = uint(rect.originY + (rect.sizeH - mHeight) / 2);
    }
#endif
}

//------------------------------------------------------------------------------
int DisplayContext::locationX()const
{
    return mLocationX;
}

//------------------------------------------------------------------------------
int DisplayContext::locationY()const
{
    return mLocationY;
}

//------------------------------------------------------------------------------
int DisplayContext::width()const
{
    return mWidth;
}

//------------------------------------------------------------------------------
int DisplayContext::height()const
{
    return mHeight;
}

//------------------------------------------------------------------------------
bool DisplayContext::isScreenDoubleBuffer()const
{
    return true;
}

//------------------------------------------------------------------------------
#else // end of WindowSystem
//------------------------------------------------------------------------------
DisplayContext::DisplayContext()
{
}

//------------------------------------------------------------------------------
#endif // end of other OS
}} // namespace
// EOF
