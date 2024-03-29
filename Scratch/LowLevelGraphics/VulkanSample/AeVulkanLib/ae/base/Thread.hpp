// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_THREAD_HPP)
#else
#define AE_BASE_INCLUDED_THREAD_HPP

namespace ae::base {
struct TimeSpanPod;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Thread
//@{
/// スレッド。
class Thread {
public:
    /// 指定時間スリープする。
    static void Sleep(const TimeSpanPod&);
};
//@}

} // namespace ae::base
#endif
// EOF
