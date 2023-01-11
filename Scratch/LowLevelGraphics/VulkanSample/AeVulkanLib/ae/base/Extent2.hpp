// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 2次元の範囲を浮動小数型で表す構造体。
struct Extent2Pod
{
    /// @name メンバ変数
    //@{
    /// 横幅。
    float width;

    /// 縦幅。
    float height;
    //@}
};

/// Extent2Pod のクラス版。
class Extent2 : public Extent2Pod {
public:
    /// @name コンストラクタ
    //@{
    /// 全て 0 で初期化。
    Extent2()
    : Extent2(0, 0)
    {
    }

    /// コピーして作成。
    Extent2(const Extent2Pod& rhs)
    : Extent2Pod(rhs)
    {
    }

    /// 各要素を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent2(float width, float height);
    //@}
};
//@}

} // namespace ae::base
// EOF
