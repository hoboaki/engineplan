// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ICONSOLECALLBACK_HPP)
#else
#define AE_BASE_INCLUDED_ICONSOLECALLBACK_HPP

#include <cstdarg>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Debug
//@{
/// コンソール用コールバックインターフェースクラス。
class IConsoleCallback {
public:
    virtual ~IConsoleCallback();

    /// @brief コンソールに書き込み要求があったときに呼ばれる。
    /// @param format printfフォーマット文字列。
    /// @param arg formatの引数。
    virtual void OnWrite(const char* format, va_list arg) = 0;
};
//@}

} // namespace ae::base
#endif
// EOF
