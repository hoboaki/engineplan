// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>
#include <ae/gfx_low/IndexBufferView.hpp>
#include <ae/gfx_low/IndexFormat.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// 頂点バッファに必要なオブジェクトをまとめた便利クラス。
class IndexBuffer {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param bufferSize バッファ全体のデータサイズ。（1以上）
    IndexBuffer(
        ::ae::gfx_low::Device* device,
        size_t bufferSize,
        ::ae::gfx_low::IndexFormat format);
    ~IndexBuffer();
    //@}

    /// @name API
    //@{
    /// ビュー。
    const ::ae::gfx_low::IndexBufferView& View() const { return *view_; }

    /// データをリソースメモリにストア。
    void StoreToResourceMemory(const ::ae::base::MemBlock& block) const;

    //@}

private:
    ::ae::gfx_low::Device& device_;
    const size_t bufferSize_ = {};
    ::ae::gfx_low::UniqueResourceMemory memory_;
    ::std::unique_ptr<::ae::gfx_low::BufferResource> bufferResource_;
    ::std::unique_ptr<::ae::gfx_low::IndexBufferView> view_;
};

} // namespace aesk
// EOF
