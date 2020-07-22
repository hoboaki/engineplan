// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_HID_IOS_HPP)
#else
#define AE_BASE_INCLUDED_HID_IOS_HPP

#include <ae/base/NonCopyable.hpp>
#include <ae/base/Touch.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// iOSのHid拡張。
class Hid_Ext : public NonCopyable
{
public:
    Touch touch;

    //------------------------------------------------------------------------------
    Hid_Ext();
};

}} // namespace
#endif
// EOF
