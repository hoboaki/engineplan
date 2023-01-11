// 文字コード：UTF-8
#pragma once

namespace ae::base {
struct Extent2Pod;
}

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Math
//@{
/// 2次元の範囲を整数型で表す構造体。
struct Extent2iPod
{
    /// @name メンバ変数
    //@{
    /// 横幅。
    int width;

    /// 縦幅。
    int height;
    //@}

    /// @name 面積
    //@{
    /// 面積がゼロか。
    bool IsZero() const { return width == 0 || height == 0; }
    //@}

    /// @name 比較
    //@{
    /// 等価比較。
    bool Equals(const Extent2iPod& rhs) const
    {
        return width == rhs.width && height == rhs.height;
    }
    //@}

    /// @name 変換
    //@{
    /// 浮動小数版に変換。
    Extent2Pod ToExtent2() const;
    //@}

    /// @name 演算子オーバーロード
    //@{
    bool operator==(const Extent2iPod& rhs) const { return Equals(rhs); }
    bool operator!=(const Extent2iPod& rhs) const { return !Equals(rhs); }
    //@}
};

/// Extent2iPod のクラス版。
class Extent2i : public Extent2iPod {
public:
    /// @name コンストラクタ
    //@{
    /// 全て 0 で初期化。
    Extent2i()
    : Extent2i(0, 0)
    {
    }

    /// コピーして作成。
    Extent2i(const Extent2iPod& rhs)
    : Extent2iPod(rhs)
    {
    }

    /// 各要素を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent2i(int width, int height);
    //@}
};
//@}

} // namespace ae::base
// EOF
