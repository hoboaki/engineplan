// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/gfx_low/BufferResource.hpp>
#include <ae/gfx_low/UniformBufferView.hpp>
#include <ae/gfx_low/UniqueResourceMemory.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// ユニフォームバッファに必要なオブジェクトをまとめた便利クラス。
class UniformBuffer {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param sizePerData データサイズ。
    /// @param dataCount 確保するデータ数。（1以上）
    /// @param isDeviceLocal VRAM上に配置するなら true を指定。
    UniformBuffer(
        ::ae::gfx_low::Device* device,
        size_t sizePerData,
        int dataCount,
        bool isDeviceLocal = false);
    ~UniformBuffer();
    //@}

    /// @name 基本API
    //@{
    /// 指定番目のバッファリソース。
    ::ae::gfx_low::BufferResource& BufferResource(int index) const {
        return bufferResources_[index];
    }

    /// 指定番目のデータインデックス値のビュー。
    const ::ae::gfx_low::UniformBufferView& View(int index) const {
        return views_[index];
    }

    /// 指定番目のデータにソースメモリにストア。
    void StoreToResourceMemory(int index, const ::ae::base::MemBlock& block)
        const;

    /// 指定番目のデータにソースメモリにストア。
    template <typename T>
    void StoreToResourceMemory(int index, const T& data) const {
        StoreToResourceMemory(
            index,
            ::ae::base::MemBlock(::ae::base::ptr_t(&data), sizeof(T)));
    }
    //@}

    /// @name データインデックス管理系API
    //@{
    /// データインデックス値を１つ進める。
    void incrementCurrentDataIndex() {
        currentDataIndex_ = (currentDataIndex_ + 1) % dataCount_;
    }
    /// 現在のデータインデックス値。
    int CurrentDataIndex() const { return currentDataIndex_; }

    /// 現在のデータインデックス値のビュー。
    const ::ae::gfx_low::UniformBufferView& CurrentView() const {
        return views_[CurrentDataIndex()];
    }

    /// 現在のデータインデックス値に対応するリソースメモリにストア。
    template <typename T>
    void StoreToCurrentResourceMemory(const T& data) const {
        StoreToCurrentResourceMemory(&data, sizeof(T));
    }

    /// 現在のデータインデックス値に対応するリソースメモリにストア。
    void StoreToCurrentResourceMemory(const ::ae::base::MemBlock& block) const {
        StoreToResourceMemory(CurrentDataIndex(), block);
    }
    //@}

private:
    ae::gfx_low::Device& device_;
    const size_t sizePerData_ = {};
    const int dataCount_ = {};
    int currentDataIndex_ = 0;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniqueResourceMemory> memories_;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::BufferResource>
        bufferResources_;
    ::ae::base::RuntimeAutoArray<::ae::gfx_low::UniformBufferView> views_;
};

} // namespace aesk
// EOF
