// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent2i.hpp>
#include <ae/base/Extent3i.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/gfx_low/ImageFormat.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>

namespace ae::gfx_low {
class BufferResource;
class ImageResource;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CopyImage コマンドに必要な情報。
class CopyImageInfo {
public:
    /// @name プロパティ
    //@{

    /// イメージデータの大きさ。（初期値：すべて0）
    base::Extent3i ImageExtent() const { return imageExtent_; }

    /// ImageExtent() の設定。（設定必須）
    CopyImageInfo& SetImageExtent(const base::Extent3iPod& extent)
    {
        imageExtent_ = extent;
        return *this;
    }

    /// 2次元用 SrcImageExtent() の設定。
    CopyImageInfo& SetImageExtent(const base::Extent2iPod& extent)
    {
        return SetImageExtent(base::Extent3i(extent, 1));
    }

    /// コピー元となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* SrcImageResource() const { return srcImageResource_.Get(); }

    /// SrcImageResource() の設定。（設定必須）
    CopyImageInfo& SetSrcImageResource(gfx_low::ImageResource* resource)
    {
        srcImageResource_.Reset(resource);
        return *this;
    }

    /// コピー元場所。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceLocation SrcSubresourceLocation() const
    {
        return srcSubresourceLocation_;
    }

    /// SrcSubresourceLocation() の設定。
    CopyImageInfo& SetSrcSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        srcSubresourceLocation_ = location;
        return *this;
    }

    /// コピー元の始点となる座標。（初期値：0,0,0）
    base::Vector3i SrcImageOffset() const { return srcImageOffset_; }

    /// SrcImageOffset() の設定。
    /// @param offset xyz それぞれ 0 以上の値。
    CopyImageInfo& SetSrcImageOffset(const base::Vector3iPod& offset);

    /// 2次元用 SrcImageOffset() の設定。
    CopyImageInfo& SetSrcImageOffset(const base::Vector2iPod& offset)
    {
        return SetSrcImageOffset(base::Vector3i(offset, 0));
    }

    /// コピー処理をする時点でのコピー元サブリソースのイメージリソースの状態。（初期値：Invalid）
    ImageResourceState SrcImageResourceState() const
    {
        return srcImageResourceState_;
    }

    /// SrcImageResourceState() の設定。
    /// @param state TransferSrcOptimal, のいずれかが指定可能。（将来的に追加予定）
    CopyImageInfo& SetSrcImageResourceState(ImageResourceState state);

    /// コピー先となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* DstImageResource() const { return dstImageResource_.Get(); }

    /// DstImageResource() の設定。（設定必須）
    CopyImageInfo& SetDstImageResource(gfx_low::ImageResource* resource)
    {
        dstImageResource_.Reset(resource);
        return *this;
    }

    /// コピー先場所。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceLocation DstSubresourceLocation() const
    {
        return dstSubresourceLocation_;
    }

    /// DstSubresourceLocation() の設定。
    CopyImageInfo& SetDstSubresourceLocation(const ImageSubresourceLocation& location)
    {
        dstSubresourceLocation_ = location;
        return *this;
    }

    /// コピー先の始点となる座標。（初期値：0,0,0）
    base::Vector3i DstImageOffset() const { return dstImageOffset_; }

    /// DstImageOffset() の設定。
    /// @param offset xyz それぞれ 0 以上の値。
    CopyImageInfo& SetDstImageOffset(const base::Vector3iPod& offset);

    /// 2次元用 DstImageOffset() の設定。
    CopyImageInfo& SetDstImageOffset(const base::Vector2iPod& offset)
    {
        return SetDstImageOffset(base::Vector3i(offset, 0));
    }

    /// コピー処理をする時点でのコピー先サブリソースのイメージリソースの状態。（初期値：Invalid）
    ImageResourceState DstImageResourceState() const
    {
        return dstImageResourceState_;
    }

    /// DstImageResourceState() の設定。
    /// @param state TransferDstOptimal, のいずれかが指定可能。（将来的に追加予定）
    CopyImageInfo& SetDstImageResourceState(ImageResourceState state);
    //@]

private:
    base::Pointer<ImageResource> srcImageResource_;
    base::Pointer<ImageResource> dstImageResource_;
    base::Extent3i imageExtent_;
    ImageSubresourceLocation srcSubresourceLocation_;
    ImageSubresourceLocation dstSubresourceLocation_;
    base::Vector3i srcImageOffset_;
    base::Vector3i dstImageOffset_;
    ImageResourceState srcImageResourceState_ = ImageResourceState::Invalid;
    ImageResourceState dstImageResourceState_ = ImageResourceState::Invalid;
};

} // namespace ae::gfx_low
// EOF
