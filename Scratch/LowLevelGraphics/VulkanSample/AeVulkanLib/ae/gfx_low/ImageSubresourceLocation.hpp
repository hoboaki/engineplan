// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ImageResource の抱える ImageSubresource の場所を示すクラス。
/// @details
/// ImageResource は複数の画像を組み合わせて１つになっていることがあります。
/// その各画像を ImageSubresource と呼んでいます。
///
/// 例えば Mip レベルを複数持つ ImageResource はそれぞれのレベル毎に
/// ImageSubresource を持っています。
///
/// 本クラス ImageSubresourceLocation は ImageResource の抱える ImageSubresource
/// １つを示すクラスとなります。
///
/// ・FaceIndex について
/// FaceIndex はキューブマップの各面の指定で使い、
/// 各番号は以下の面に対応します。
/// 0：+X
/// 1：-X
/// 2：+Y
/// 3：-Y
/// 4：+Z
/// 5：-Z
class ImageSubresourceLocation {
public:
    /// @name プロパティ
    //@{
    /// Mip レベル。（初期値：0）
    int MipLevel() const { return mipLevel_; }

    /// MipLevel() の設定。
    /// @param level 0以上。
    ImageSubresourceLocation& SetMipLevel(int level);

    /// 配列番号。（初期値：0）
    int ArrayIndex() const { return arrayIndex_; }

    /// ArrayIndex() の設定。
    /// @param index 0以上。
    ImageSubresourceLocation& SetArrayIndex(int index);

    /// 面番号（初期値：0）
    /// @details
    /// 面番号についてはクラスの詳細コメントを参照。
    int FaceIndex() const { return faceIndex_; }

    /// FaceIndex() の設定。
    /// @param index 0以上。
    ImageSubresourceLocation& SetFaceIndex(int index);
    //@}

private:
    int mipLevel_ = 0;
    int arrayIndex_ = 0;
    int faceIndex_ = 0;
};

} // namespace ae::gfx_low
// EOF
