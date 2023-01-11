// 文字コード：UTF-8
#pragma once

namespace ae::base {
struct Extent2iPod;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 3次元の範囲を整数型で表す構造体。
struct Extent3iPod
{
    /// @name メンバ変数
    //@{
    /// 横幅。
    int width;

    /// 縦幅。
    int height;

    /// 奥幅。
    int depth;
    //@}

    /// @name 体積
    //@{
    /// 体積がゼロか。
    bool IsZero() const { return width == 0 || height == 0 || depth == 0; }
    //@}

    /// @name 比較
    //@{
    /// 等価比較。
    bool Equals(const Extent3iPod& rhs) const
    {
        return width == rhs.width && height == rhs.height && depth == rhs.depth;
    }
    //@}

    /// @name 演算子オーバーロード
    //@{
    bool operator==(const Extent3iPod& rhs) const { return Equals(rhs); }
    bool operator!=(const Extent3iPod& rhs) const { return !Equals(rhs); }
    //@}
};

/// Extent3iPod のクラス版。
class Extent3i : public Extent3iPod {
public:
    /// @name コンストラクタ
    //@{
    /// 全て 0 で初期化。
    Extent3i()
    : Extent3i(0, 0, 0)
    {
    }

    /// コピーして作成。
    Extent3i(const Extent3iPod& rhs)
    : Extent3iPod(rhs)
    {
    }

    /// Extent2i と depth を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent3i(const Extent2iPod& extent, int depth);

    /// 各要素を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent3i(int width, int height, int depth);
    //@}
};
//@}

} // namespace ae::base
// EOF
