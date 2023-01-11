// 文字コード：UTF-8
#include <ae/base/DisplayContext.hpp>

// includes
#include <ae/base/SdkHeader.hpp>

#if defined(AE_BASE_OS_MACOSX)
#include <ae_mac_os/AeBaseNSScreen.h>
#endif

//------------------------------------------------------------------------------
namespace ae::base {
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
: locationX_(0)
, locationY_(0)
, width_(tDefaultWidth)
, height_(tDefaultHeight)
, isScreenDoubleBuffer_(true)
{
    // センタリング
    SetLocationToCenter();
}

//------------------------------------------------------------------------------
void DisplayContext::SetLocationToCenter()
{
#if defined(AE_BASE_OS_WINDOWS)
    // 情報取得
    HWND hwnd = GetDesktopWindow();
    HDC hdc = GetDC(hwnd);
    const int dispWidth = GetDeviceCaps(hdc, HORZRES);
    const int dispHeight = GetDeviceCaps(hdc, VERTRES);
    ReleaseDC(hwnd, hdc);

    // 位置設定
    if (width_ < dispWidth) {
        locationX_ = (dispWidth - width_) / 2;
    }
    if (height_ < dispHeight) {
        locationY_ = (dispHeight - height_) / 2;
    }
#elif defined(AE_BASE_OS_MACOSX)
    // 情報取得
    AeBaseNSRect rect = {};
    AeBaseNSScreen_GetMainScreenVisibleFrame(&rect);

    // 位置設定
    if (width_ < rect.sizeW) {
        locationX_ = uint(rect.originX + (rect.sizeW - width_) / 2);
    }
    if (height_ < rect.sizeH) {
        locationY_ = uint(rect.originY + (rect.sizeH - height_) / 2);
    }
#endif
}

//------------------------------------------------------------------------------
int DisplayContext::LocationX() const
{
    return locationX_;
}

//------------------------------------------------------------------------------
int DisplayContext::LocationY() const
{
    return locationY_;
}

//------------------------------------------------------------------------------
int DisplayContext::Width() const
{
    return width_;
}

//------------------------------------------------------------------------------
int DisplayContext::Height() const
{
    return height_;
}

//------------------------------------------------------------------------------
bool DisplayContext::IsScreenDoubleBuffer() const
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
} // namespace ae::base
// EOF
