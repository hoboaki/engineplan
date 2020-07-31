// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

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
    ResourceMemory()
    : instance_() {}
    //@}

    /// @name プロパティ
    //@{
    /// 有効なメモリを指し示しているか。
    bool IsValid() const { return instance_ != ::vk::DeviceMemory(); }
    //@}

    /// @name 内部処理用機能
    //@{
    ResourceMemory(const ::vk::DeviceMemory& instance)
    : instance_(instance) {}

    ::vk::DeviceMemory Instance_() const { return instance_; }
    //@}

private:
    ::vk::DeviceMemory instance_;
};

} // namespace gfx_low
} // namespace ae
// EOF
