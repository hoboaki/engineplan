// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ImageSubresourceLocation.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ImageResource の抱える ImageSubresource の範囲を示すクラス。
/// @details
/// ・キューブイメージの ArrayLength の指定について
/// 対象となる ImageResource の種類が ImageResourceKind::ImageCube で
/// かつ BaseLocation().FaceIndex() が 1 以上の場合、
/// ArrayLength() は 1 以外の値を指定することができません。
class ImageSubresourceRange {
public:
    /// @name プロパティ
    //@{
    /// 起点となる位置。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceLocation BaseLocation() const { return baseLocation_; }

    /// BaseLocation() の設定。
    ImageSubresourceRange& SetBaseLocation(
        const ImageSubresourceLocation& location)
    {
        baseLocation_ = location;
        return *this;
    }

    /// Mip レベル数。（初期値：1）
    int MipLevels() const { return mipLevels_; }

    /// MipLevel() の設定。
    /// @param level 0以上。
    ImageSubresourceRange& SetMipLevels(int levels);

    /// 配列長。（初期値：1）
    int ArrayLength() const { return arrayLength_; }

    /// ArrayLength() の設定。
    /// @param length 1以上。
    /// @details
    /// 対象の ImageResource がキューブイメージの場合、指定に制限があります。
    /// 詳しくは本クラスの注釈を参照してください。
    ImageSubresourceRange& SetArrayLength(int length);
    //@}

private:
    ImageSubresourceLocation baseLocation_;
    int mipLevels_ = 1;
    int arrayLength_ = 1;
};

} // namespace ae::gfx_low
// EOF
