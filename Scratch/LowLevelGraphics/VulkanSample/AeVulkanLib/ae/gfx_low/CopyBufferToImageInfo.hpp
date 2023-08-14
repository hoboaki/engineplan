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

/// CopyBufferToImage コマンドに必要な情報。
class CopyBufferToImageInfo {
public:
    /// @name プロパティ
    //@{
    /// コピー元イメージデータが格納されている BufferResource のポインタ。（初期値：nullptr）
    BufferResource* SrcBufferResource() const
    {
        return srcBufferResource_.Get();
    }

    /// SrcBufferResource() の設定。（設定必須）
    CopyBufferToImageInfo& SetSrcBufferResource(
        gfx_low::BufferResource* resource)
    {
        srcBufferResource_.Reset(resource);
        return *this;
    }

    /// BufferResource の抱える ResourceMemory
    /// の先頭アドレスからコピー元イメージデータまでのオフセット値。（初期値：0）
    size_t SrcBufferOffset() const { return srcBufferOffset_; }

    /// BufferOffset() の設定。
    CopyBufferToImageInfo& SetSrcBufferOffset(size_t offset)
    {
        srcBufferOffset_ = offset;
        return *this;
    }

    /// コピー元イメージデータのY方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t SrcBufferRowPitch() const { return srcBufferRowPitch_; }

    /// SrcBufferRowPitch() の設定。
    CopyBufferToImageInfo& SetSrcBufferRowPitch(size_t pitch)
    {
        srcBufferRowPitch_ = pitch;
        return *this;
    }

    /// コピー元イメージデータのZ方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t SrcBufferDepthPitch() const { return srcBufferDepthPitch_; }

    /// SrcBufferDepthPitch() の設定。
    CopyBufferToImageInfo& SetSrcBufferDepthPitch(size_t pitch)
    {
        srcBufferDepthPitch_ = pitch;
        return *this;
    }

    /// コピー元イメージデータの大きさ。（初期値：すべて0）
    base::Extent3i SrcImageExtent() const { return srcImageExtent_; }

    /// SrcImageExtent() の設定。（設定必須）
    CopyBufferToImageInfo& SetSrcImageExtent(const base::Extent3iPod& extent)
    {
        srcImageExtent_ = extent;
        return *this;
    }

    /// 2次元用 SrcImageExtent() の設定。
    CopyBufferToImageInfo& SetSrcImageExtent(const base::Extent2iPod& extent)
    {
        return SetSrcImageExtent(base::Extent3i(extent, 1));
    }

    /// コピー元イメージデータのフォーマット。（初期値：Invalid）
    ImageFormat SrcImageFormat() const { return srcImageFormat_; }

    /// SrcImageFormat() の設定。（設定必須）
    CopyBufferToImageInfo& SetSrcImageFormat(ImageFormat format);

    /// コピー先となる ImageResource
    /// のポインタ。（初期値：nullptr）
    ImageResource* DstImageResource() const { return dstImageResource_.Get(); }

    /// DstImageResource() の設定。（設定必須）
    CopyBufferToImageInfo& SetDstImageResource(
        gfx_low::ImageResource* resource)
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
    CopyBufferToImageInfo& SetDstSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        dstSubresourceLocation_ = location;
        return *this;
    }

    /// コピー先の始点となる座標。（初期値：0,0,0）
    base::Vector3i DstImageOffset() const { return dstImageOffset_; }

    /// DstImageOffset() の設定。
    /// @param offset xyz それぞれ 0 以上の値。
    CopyBufferToImageInfo& SetDstImageOffset(const base::Vector3iPod& offset);

    /// 2次元用 DstImageOffset() の設定。
    CopyBufferToImageInfo& SetDstImageOffset(const base::Vector2iPod& offset)
    {
        return SetDstImageOffset(base::Vector3i(offset, 0));
    }

    /// コピー処理をする時点でのコピー先サブリソースのイメージリソースの状態。（初期値：Invalid）
    ImageResourceState DstImageResourceState() const
    {
        return dstImageResourceState_;
    }

    /// DstImageResourceState() の設定。
    /// @param state CopyDst, のいずれかが指定可能。（将来的に追加予定）
    CopyBufferToImageInfo& SetDstImageResourceState(ImageResourceState state);
    //@]

private:
    base::Pointer<BufferResource> srcBufferResource_;
    base::Pointer<ImageResource> dstImageResource_;
    size_t srcBufferOffset_ = 0;
    size_t srcBufferRowPitch_ = 0;
    size_t srcBufferDepthPitch_ = 0;
    base::Extent3i srcImageExtent_;
    ImageSubresourceLocation dstSubresourceLocation_;
    base::Vector3i dstImageOffset_;
    ImageFormat srcImageFormat_ = ImageFormat::Invalid;
    ImageResourceState dstImageResourceState_ = ImageResourceState::Invalid;
};

} // namespace ae::gfx_low
// EOF
