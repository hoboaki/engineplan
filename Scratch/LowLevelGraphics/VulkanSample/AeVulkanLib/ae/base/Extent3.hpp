// 文字コード：UTF-8
#pragma once

namespace ae::base {
struct Extent2Pod;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 3次元の範囲を整数型で表す構造体。
struct Extent3Pod
{
    /// @name メンバ変数
    //@{
    /// 横幅。
    float width;

    /// 縦幅。
    float height;

    /// 奥幅。
    float depth;
    //@}
};

/// Extent3Pod のクラス版。
class Extent3 : public Extent3Pod {
public:
    /// @name コンストラクタ
    //@{
    /// 全て 0 で初期化。
    Extent3()
    : Extent3(0, 0, 0)
    {
    }

    /// コピーして作成。
    Extent3(const Extent3Pod& rhs)
    : Extent3Pod(rhs)
    {
    }

    /// Extent2i と depth を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent3(const Extent2Pod& extent, float depth);

    /// 各要素を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent3(float width, float height, float depth);
    //@}
};
//@}

} // namespace ae::base
// EOF
