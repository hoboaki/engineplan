// 文字コード：UTF-8
#pragma once

#include <ae/base/Extent2i.hpp>
#include <ae/base/Extent3i.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>

namespace ae {
namespace gfx_low {
class BufferResource;
class ImageResource;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// CopyBufferToImage コマンドに必要な情報。
class CopyBufferToImageInfo {
public:
    /// @name プロパティ
    //@{
    /// コピー元イメージデータが可能されている BufferResource
    /// のポインタ。（初期値：nullptr）
    BufferResource* SrcBufferResource() const {
        return srcBufferResource_.Get();
    }

    /// SrcBufferResource() の設定。（設定必須）
    CopyBufferToImageInfo& SetSrcBufferResource(
        gfx_low::BufferResource* resource) {
        srcBufferResource_.Reset(resource);
        return *this;
    }

    /// BufferResource の抱える ResourceMemory
    /// の先頭アドレスからコピー元イメージデータまでのオフセット値。（初期値：0）
    size_t SrcBufferOffset() const { return srcBufferOffset_; }

    /// BufferOffset() の設定。
    CopyBufferToImageInfo& SetSrcBufferOffset(size_t offset) {
        srcBufferOffset_ = offset;
        return *this;
    }

    /// コピー元イメージデータのY方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t SrcBufferRowPitch() const { return srcBufferRowPitch_; }

    /// SrcBufferRowPitch() の設定。
    CopyBufferToImageInfo& SetSrcBufferRowPitch(size_t pitch) {
        srcBufferRowPitch_ = pitch;
        return *this;
    }

    /// コピー元イメージデータのZ方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t SrcBufferDepthPitch() const { return srcBufferDepthPitch_; }

    /// SrcBufferDepthPitch() の設定。
    CopyBufferToImageInfo& SetSrcBufferDepthPitch(size_t pitch) {
        srcBufferDepthPitch_ = pitch;
        return *this;
    }

    /// コピー元イメージデータの範囲。（初期値：すべて0）
    base::Extent3i SrcBufferImageExtent() const {
        return srcBufferImageExtent_;
    }

    /// SrcBufferImageExtent() の設定。（設定必須）
    CopyBufferToImageInfo& SetSrcBufferImageExtent(
        const base::Extent3iPod& extent) {
        srcBufferImageExtent_ = extent;
        return *this;
    }

    /// 2次元用 SrcBufferImageExtent() の設定。
    CopyBufferToImageInfo& SetExtent(const base::Extent2iPod& extent) {
        srcBufferImageExtent_ = base::Extent3i(extent, 1);
        return *this;
    }

    /// コピー先となる ImageResource
    /// のポインタ。（初期値：nullptr）
    ImageResource* DstImageResource() const { return dstImageResource_.Get(); }

    /// DstImageResource() の設定。（設定必須）
    CopyBufferToImageInfo& SetDstImageResource(
        gfx_low::ImageResource* resource) {
        dstImageResource_.Reset(resource);
        return *this;
    }

    /// コピー先場所。（初期値：デフォルトコンストラクタの値） 
    ImageSubresourceLocation DstSubresourceLocation() const {
        return dstSubresourceLocation_;
    }

    /// DstSubresourceLocation() の設定。
    CopyBufferToImageInfo& SetDstSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        dstSubresourceLocation_ = location;
        return *this;
    }

    /// コピー処理をする時点でのコピー先サブリソースのイメージリソースの状態。（初期値：Invalid）
    ImageResourceState DstImageResourceState() const {
        return dstImageResourceState_;
    }

    /// DstImageResourceState() の設定。
    /// @param state TransferDstOptimal, のいずれかが指定可能。（将来的に追加予定）
    CopyBufferToImageInfo& SetDstImageResourceState(ImageResourceState state);
    //@]

private:
    base::Pointer<BufferResource> srcBufferResource_;
    base::Pointer<ImageResource> dstImageResource_;
    size_t srcBufferOffset_ = 0;
    size_t srcBufferRowPitch_ = 0;
    size_t srcBufferDepthPitch_ = 0;
    base::Extent3i srcBufferImageExtent_;
    ImageSubresourceLocation dstSubresourceLocation_;
    ImageResourceState dstImageResourceState_ = ImageResourceState::Invalid;
};

} // namespace gfx_low
} // namespace ae
// EOF
