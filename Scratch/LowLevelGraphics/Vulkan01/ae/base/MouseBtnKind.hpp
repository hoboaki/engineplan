// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MOUSEBTNKIND_HPP)
#else
#define AE_BASE_INCLUDED_MOUSEBTNKIND_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// マウスのボタンの種類。
struct MouseBtnKind
{
    enum EnumType
    {
        L, ///< 左。
        R, ///< 右。(副ボタン)
        M, ///< 中。(3ボタン)

        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
