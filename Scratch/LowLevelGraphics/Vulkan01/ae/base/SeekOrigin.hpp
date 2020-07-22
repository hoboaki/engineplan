// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_SEEKORIGIN_HPP)
#else
#define AE_BASE_INCLUDED_SEEKORIGIN_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-IO
//@{
/// Seek関数の基準。
struct SeekOrigin
{
    enum EnumType
    {
        Begin,   ///< 先頭。
        Current, ///< 現在位置。
        End,     ///< 末尾。
        
        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
