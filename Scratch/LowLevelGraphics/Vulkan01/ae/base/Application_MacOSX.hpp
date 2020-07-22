// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_APPLICATION_MACOSX_HPP)
#else
#define AE_BASE_INCLUDED_APPLICATION_MACOSX_HPP

#include <ae/base/Bool.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// MacOSX環境でのApplicationの拡張。
class Application_Ext
{
public:
    //============================================================
    s64 prevUpdateTicks;
    Bool32 doQuit;

    //============================================================
    Application_Ext();
    ~Application_Ext();
};
//@}

}} // namespace
#endif
// EOF
