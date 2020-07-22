// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_APPLICATION_WINDOWS_HPP)
#else
#define AE_BASE_INCLUDED_APPLICATION_WINDOWS_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/Time.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// Windows環境でのApplicationの拡張。
class Application_Ext
{
public:
    //============================================================
    u64  prevUSec;
    Bool32 doQuit;

    //============================================================
    Application_Ext();
};
//@}

}} // namespace
#endif
// EOF
