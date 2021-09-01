// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/VertexAttributeInfo.hpp>
#include <ae/gfx_low/VertexBufferView.hpp>
#include <ae/gfx_low/VertexBufferLayoutINfo.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// 頂点バッファに必要なオブジェクトをまとめた便利クラス。
class VertexBuffer
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param bufferSize バッファ全体のデータサイズ。（1以上）
    VertexBuffer(
        ::ae::gfx_low::Device* device,
        size_t bufferSize,
        const ::ae::gfx_low::VertexBufferLayoutInfo& layoutInfo
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
