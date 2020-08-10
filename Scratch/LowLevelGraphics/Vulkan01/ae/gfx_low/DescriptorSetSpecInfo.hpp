// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class ShaderBindingInfo;
;
} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// DescriptorSet の仕様情報。
/// @todo インラインコンスタント対応。
class DescriptorSetSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// UniformBuffer のバインド情報の数。（初期値：0）
    int UniformBufferInfosCount() const { return uniformBufferInfosCount_; }

    /// UniformBufferInfosCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetUniformBufferInfosCount(int count);

    /// UniformBuffer のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* UniformBufferInfos() const {
        return uniformBufferInfos_.Get();
    }

    /// UniformBufferInfos() 設定。
    DescriptorSetSpecInfo& SetUniformBufferInfos(
        const ShaderBindingInfo* infos) {
        uniformBufferInfos_.Reset(infos);
        return *this;
    }

    /// StorageBufferInfos のバインド情報数。（初期値：0）
    int StorageBufferInfosCount() const { return storageBufferInfosCount_; }

    /// StorageBufferInfosCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetStorageBufferInfosCount(int count);

    /// StorageBuffer のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* StorageBufferInfos() const {
        return storageBufferInfos_.Get();
    }

    /// StorageBufferInfos() 設定。
    DescriptorSetSpecInfo& SetStorageBufferInfos(
        const ShaderBindingInfo* infos) {
        storageBufferInfos_.Reset(infos);
        return *this;
    }

    /// SampledImage のバインド情報数。（初期値：0）
    int SampledImageInfosCount() const { return sampledImageInfosCount_; }

    /// SampledImageInfosCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetSampledImageInfosCount(int count);

    /// SampledImage のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* SampledImageInfos() const {
        return sampledImageInfos_.Get();
    }

    /// SampledImageInfos() 設定。
    DescriptorSetSpecInfo& SetSampledImageInfos(
        const ShaderBindingInfo* infos) {
        sampledImageInfos_.Reset(infos);
        return *this;
    }

    /// StorageImage のバインド情報数。（初期値：0）
    int StorageImageInfosCount() const { return storageImageInfosCount_; }

    /// StorageImageInfosCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetStorageImageInfosCount(int count);

    /// StorageImage のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* StorageImageInfos() const {
        return storageImageInfos_.Get();
    }

    /// StorageImageInfos() 設定。
    DescriptorSetSpecInfo& SetStorageImageInfos(
        const ShaderBindingInfo* infos) {
        storageImageInfos_.Reset(infos);
        return *this;
    }

    /// Sampler のバインド数。（初期値：0）
    int SamplerInfosCount() const { return samplerInfosCount_; }

    /// SamplerCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetSamplerInfosCount(int count);

    /// Sampler のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* SamplerInfos() const {
        return samplerInfos_.Get();
    }

    /// SamplerInfos() 設定。
    DescriptorSetSpecInfo& SetSamplerInfos(
        const ShaderBindingInfo* infos) {
        samplerInfos_.Reset(infos);
        return *this;
    }
    //@}

private:
    int uniformBufferInfosCount_ = 0;
    int storageBufferInfosCount_ = 0;
    int sampledImageInfosCount_ = 0;
    int storageImageInfosCount_ = 0;
    int samplerInfosCount_ = 0;
    base::Pointer<const ShaderBindingInfo> uniformBufferInfos_;
    base::Pointer<const ShaderBindingInfo> storageBufferInfos_;
    base::Pointer<const ShaderBindingInfo> sampledImageInfos_;
    base::Pointer<const ShaderBindingInfo> storageImageInfos_;
    base::Pointer<const ShaderBindingInfo> samplerInfos_;
};

} // namespace gfx_low
} // namespace ae
// EOF
