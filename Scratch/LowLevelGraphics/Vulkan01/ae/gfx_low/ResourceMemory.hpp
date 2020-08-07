// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class ResourceMemoryAddress;
}
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// リソース用メモリを扱うクラス。
/// @details
/// ImageResource、BufferResource、ShaderResource
/// 等リソースの扱うメモリを扱うクラスです。
///
/// メモリの確保と破棄は Device に対して行います。
///
/// ResourceMemory クラス自体はただのデータ構造なので、
/// コンストラクタやデストラクタでメモリの確保や破棄は行いません。
class ResourceMemory {
public:
    /// @name コンストラクタ
    //@{
    /// IsValid() == false なオブジェクトを作成。
    ResourceMemory() {}
    //@}

    /// @name プロパティ
    //@{
    /// 有効なメモリを指し示しているか。
    bool IsValid() const { 
        return nativeObject_ != ::vk::DeviceMemory() || head_ != nullptr; 
    }

    /// ResourceMemoryAddress オブジェクトを取得。
    /// @param offset 先頭からのオフセットバイト数。
    ResourceMemoryAddress Address(size_t offset = 0) const;
    //@}

    /// @name 内部処理用機能
    //@{
    ResourceMemory(const ::vk::DeviceMemory& instance)
    : nativeObject_(instance) {}

    ResourceMemory(void* head)
    : head_(head) {}

    ::vk::DeviceMemory NativeObject_() const { return nativeObject_; }

    void* Head_() const { return head_; }
    //@}

private:
    ::vk::DeviceMemory nativeObject_ = ::vk::DeviceMemory();
    void* head_ = nullptr;
};

} // namespace gfx_low
} // namespace ae
// EOF
