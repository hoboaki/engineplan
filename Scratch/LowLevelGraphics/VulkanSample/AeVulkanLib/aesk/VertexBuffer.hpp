// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/VertexAttributeInfo.hpp>
#include <ae/gfx_low/VertexBufferView.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// 頂点バッファに必要なオブジェクトをまとめた便利クラス。
class VertexBuffer
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param stride ::ae::gfx_low::VertesxBufferLayoutInfo::Stride() に対応する値。
    /// @param bufferSize バッファ全体のデータサイズ。（1以上）
    VertexBuffer(
        ::ae::gfx_low::Device* device,
        int stride,
        size_t bufferSize
        );
    ~VertexBuffer();
    //@}

    /// @name API
    //@{
    /// ビュー。
    const ::ae::gfx_low::VertexBufferView& View() const { return *view_; }

    /// データをリソースメモリにストア。
    void StoreToResourceMemory(const ::ae::base::MemBlock& block) const;

    //@}

private:
    ::ae::gfx_low::Device& device_;
    const size_t bufferSize_ = {};
    ::ae::gfx_low::UniqueResourceMemory memory_;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> bufferResource_;
    ::std::unique_ptr<::ae::gfx_low::VertexBufferView> view_;

};

}
// EOF
