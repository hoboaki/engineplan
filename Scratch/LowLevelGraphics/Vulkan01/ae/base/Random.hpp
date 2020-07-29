// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RANDOM_HPP)
#else
#define AE_BASE_INCLUDED_RANDOM_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// @brief 乱数。
/// @details
/// アルゴリズムはxorshiftを採用しています。
class Random
{
public:
    /// @name コンストラクタ
    //@{
    Random(); ///< デフォルトの設定で作成。
    Random(u32 x, u32 y, u32 z, u32 w); ///< Seed値を指定して作成。
    //@}

    /// @name 乱数取得
    //@{
    u32 Rand();
    u32 RandU32(u32 aTerm); ///< 0 <= return < aTerm。
    s32 RandS32(s32 aTerm); ///< 0 <= return < aTerm。
    s32 RandS32(s32 aMin, s32 aMax); ///< aMin <= return <= aMax。
    f32 RandF32N(); ///<  0.0f <= return <= 1.0f。
    f32 RandF32SN(); ///< -1.0f <= return <= 1.0f。
    unsigned int operator()(unsigned int aTerm); ///< std::random_shuffle用。
    //@}

private:
    u32 x_;
    u32 y_;
    u32 z_;
    u32 w_;
};
//@}

}} // namespace
#endif
// EOF
