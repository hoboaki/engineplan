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

/// CopyBuffer コマンドに必要な情報。
class CopyBufferInfo {
public:
    /// @name プロパティ
    //@{
    /// コピー元バッファデータが格納されている BufferResource のポインタ。（初期値：nullptr）
    BufferResource* SrcBufferResource() const
    {
        return srcBufferResource_.Get();
    }

    /// SrcBufferResource() の設定。（設定必須）
    CopyBufferInfo& SetSrcBufferResource(gfx_low::BufferResource* resource)
    {
        srcBufferResource_.Reset(resource);
        return *this;
    }

    /// BufferResource の抱える ResourceMemory の
    /// 先頭アドレスからコピー元バッファデータまでのオフセット値。（初期値：0）
    size_t SrcBufferOffset() const { return srcBufferOffset_; }

    /// BufferOffset() の設定。
    CopyBufferInfo& SetSrcBufferOffset(size_t offset)
    {
        srcBufferOffset_ = offset;
        return *this;
    }

    /// コピー先となる BufferResource のポインタ。（初期値：nullptr）
    BufferResource* DstBufferResource() const
    {
        return dstBufferResource_.Get();
    }

    /// DstBufferResource() の設定。（設定必須）
    CopyBufferInfo& SetDstBufferResource(gfx_low::BufferResource* resource)
    {
        dstBufferResource_.Reset(resource);
        return *this;
    }

    /// BufferResource の抱える ResourceMemory の
    /// 先頭アドレスからコピー先バッファデータまでのオフセット値。（初期値：0）
    size_t DstBufferOffset() const { return dstBufferOffset_; }

    /// BufferOffset() の設定。
    CopyBufferInfo& SetDstBufferOffset(size_t offset)
    {
        dstBufferOffset_ = offset;
        return *this;
    }

    /// コピーするバイトサイズ。（初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定。（設定必須）
    CopyBufferInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }
    //@]

private:
    base::Pointer<BufferResource> srcBufferResource_;
    base::Pointer<BufferResource> dstBufferResource_;
    size_t srcBufferOffset_ = 0;
    size_t dstBufferOffset_ = 0;
    size_t size_ = 0;
};

} // namespace ae::gfx_low
// EOF
