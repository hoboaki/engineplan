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

/// CopyImageToBuffer コマンドに必要な情報。
class CopyImageToBufferInfo {
public:
    /// @name プロパティ
    //@{
    /// コピー元となる ImageResource のポインタ。（初期値：nullptr）
    ImageResource* SrcImageResource() const { return srcImageResource_.Get(); }

    /// SrcImageResource() の設定。（設定必須）
    CopyImageToBufferInfo& SetSrcImageResource(gfx_low::ImageResource* resource)
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
    CopyImageToBufferInfo& SetSrcSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        srcSubresourceLocation_ = location;
        return *this;
    }

    /// コピー元の始点となる座標。（初期値：0,0,0）
    base::Vector3i SrcImageOffset() const { return srcImageOffset_; }

    /// SrcImageOffset() の設定。
    /// @param offset xyz それぞれ 0 以上の値。
    CopyImageToBufferInfo& SetSrcImageOffset(const base::Vector3iPod& offset);

    /// 2次元用 SrcImageOffset() の設定。
    CopyImageToBufferInfo& SetSrcImageOffset(const base::Vector2iPod& offset)
    {
        return SetSrcImageOffset(base::Vector3i(offset, 0));
    }

    /// コピー処理をする時点でのコピー元サブリソースのイメージリソースの状態。（初期値：Invalid）
    ImageResourceState SrcImageResourceState() const
    {
        return srcImageResourceState_;
    }

    /// SrcImageResourceState() の設定。
    /// @param state CopyDst, のいずれかが指定可能。（将来的に追加予定）
    CopyImageToBufferInfo& SetSrcImageResourceState(ImageResourceState state);

    /// コピー先となる BufferResource のポインタ。（初期値：nullptr）
    BufferResource* DstBufferResource() const
    {
        return dstBufferResource_.Get();
    }

    /// DstBufferResource() の設定。（設定必須）
    CopyImageToBufferInfo& SetDstBufferResource(
        gfx_low::BufferResource* resource)
    {
        dstBufferResource_.Reset(resource);
        return *this;
    }

    /// BufferResource の抱える ResourceMemory の先頭アドレスからコピー元イメージデータまでのオフセット値。（初期値：0）
    size_t DstBufferOffset() const { return dstBufferOffset_; }

    /// BufferOffset() の設定。
    CopyImageToBufferInfo& SetDstBufferOffset(size_t offset)
    {
        dstBufferOffset_ = offset;
        return *this;
    }

    /// コピー先イメージデータのY方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t DstBufferRowPitch() const { return dstBufferRowPitch_; }

    /// DstBufferRowPitch() の設定。
    CopyImageToBufferInfo& SetDstBufferRowPitch(size_t pitch)
    {
        dstBufferRowPitch_ = pitch;
        return *this;
    }

    /// コピー先イメージデータのZ方向に+1移動する際のバイトサイズ。（初期値：0）
    size_t DstBufferDepthPitch() const { return dstBufferDepthPitch_; }

    /// DstBufferDepthPitch() の設定。
    CopyImageToBufferInfo& SetDstBufferDepthPitch(size_t pitch)
    {
        dstBufferDepthPitch_ = pitch;
        return *this;
    }

    /// コピー先イメージデータのフォーマット。（初期値：Invalid）
    ImageFormat DstImageFormat() const { return dstImageFormat_; }

    /// DstImageFormat() の設定。（設定必須）
    CopyImageToBufferInfo& SetDstImageFormat(ImageFormat format);

    /// コピー先イメージデータの大きさ。（初期値：すべて0）
    base::Extent3i DstImageExtent() const { return dstImageExtent_; }

    /// DstImageExtent() の設定。（設定必須）
    CopyImageToBufferInfo& SetDstImageExtent(const base::Extent3iPod& extent)
    {
        dstImageExtent_ = extent;
        return *this;
    }

    /// 2次元用 DstImageExtent() の設定。
    CopyImageToBufferInfo& SetDstImageExtent(const base::Extent2iPod& extent)
    {
        return SetDstImageExtent(base::Extent3i(extent, 1));
    }
    //@]

private:
    base::Pointer<ImageResource> srcImageResource_;
    base::Pointer<BufferResource> dstBufferResource_;
    size_t dstBufferOffset_ = 0;
    size_t dstBufferRowPitch_ = 0;
    size_t dstBufferDepthPitch_ = 0;
    base::Extent3i dstImageExtent_;
    ImageSubresourceLocation srcSubresourceLocation_;
    base::Vector3i srcImageOffset_;
    ImageFormat dstImageFormat_ = ImageFormat::Invalid;
    ImageResourceState srcImageResourceState_ = ImageResourceState::Invalid;
};

} // namespace ae::gfx_low
// EOF
