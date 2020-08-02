// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Math
//@{
/// 2次元の範囲を整数型で表す構造体。
struct Extent2iPod {
    /// @name メンバ変数
    //@{
    /// 横幅。
    int width;

    /// 縦幅。
    int height;
    //@}
};

/// Extent2iPod のクラス版。
class Extent2i : public Extent2iPod {
public:
    /// @name コンストラクタ
    //@{
    /// 全て 0 で初期化。
    Extent2i()
    : Extent2i(0, 0) {}

    /// 各要素を指定して初期化。
    /// @details
    /// 全要素が 0 以上である必要があります。
    Extent2i(int width, int height);
    //@}
};
//@}

} // namespace base
} // namespace ae
// EOF
