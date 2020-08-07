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
class DescriptorSetSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// UniformBuffer のバインド数。（初期値：0）
    int UniformBufferCount() const { return uniformBufferCount_; }

    /// UniformBufferCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetUniformBufferCount(int count);

    /// UniformBuffer のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* UniformBufferBindingInfos() const {
        return uniformBufferBindingInfos_.Get();
    }

    /// UniformBufferBindingInfos() 設定。
    DescriptorSetSpecInfo& SetUniformBufferBindingInfos(
        const ShaderBindingInfo* infos) {
        uniformBufferBindingInfos_.Reset(infos);
        return *this;
    }

    /// StorageBuffer のバインド数。（初期値：0）
    int StorageBufferCount() const { return storageBufferCount_; }

    /// StorageBufferCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetStorageBufferCount(int count);

    /// StorageBuffer のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* StorageBufferBindingInfos() const {
        return storageBufferBindingInfos_.Get();
    }

    /// StorageBufferBindingInfos() 設定。
    DescriptorSetSpecInfo& SetStorageBufferBindingInfos(
        const ShaderBindingInfo* infos) {
        storageBufferBindingInfos_.Reset(infos);
        return *this;
    }

    /// SampledImage のバインド数。（初期値：0）
    int SampledImageCount() const { return sampledImageCount_; }

    /// SampledImageCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetSampledImageCount(int count);

    /// SampledImage のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* SampledImageBindingInfos() const {
        return sampledImageBindingInfos_.Get();
    }

    /// SampledImageBindingInfos() 設定。
    DescriptorSetSpecInfo& SetSampledImageBindingInfos(
        const ShaderBindingInfo* infos) {
        sampledImageBindingInfos_.Reset(infos);
        return *this;
    }

    /// StorageImage のバインド数。（初期値：0）
    int StorageImageCount() const { return storageImageCount_; }

    /// StorageImageCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetStorageImageCount(int count);

    /// StorageImage のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* StorageImageBindingInfos() const {
        return storageImageBindingInfos_.Get();
    }

    /// StorageImageBindingInfos() 設定。
    DescriptorSetSpecInfo& SetStorageImageBindingInfos(
        const ShaderBindingInfo* infos) {
        storageImageBindingInfos_.Reset(infos);
        return *this;
    }

    /// Sampler のバインド数。（初期値：0）
    int SamplerCount() const { return samplerCount_; }

    /// SamplerCount() の設定。
    /// @param count 0 以上。
    DescriptorSetSpecInfo& SetSamplerCount(int count);

    /// Sampler のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* SamplerBindingInfos() const {
        return samplerBindingInfos_.Get();
    }

    /// SamplerBindingInfos() 設定。
    DescriptorSetSpecInfo& SetSamplerBindingInfos(
        const ShaderBindingInfo* infos) {
        samplerBindingInfos_.Reset(infos);
        return *this;
    }
    //@}

private:
    int uniformBufferCount_ = 0;
    int storageBufferCount_ = 0;
    int sampledImageCount_ = 0;
    int storageImageCount_ = 0;
    int samplerCount_ = 0;
    base::Pointer<const ShaderBindingInfo> uniformBufferBindingInfos_;
    base::Pointer<const ShaderBindingInfo> storageBufferBindingInfos_;
    base::Pointer<const ShaderBindingInfo> sampledImageBindingInfos_;
    base::Pointer<const ShaderBindingInfo> storageImageBindingInfos_;
    base::Pointer<const ShaderBindingInfo> samplerBindingInfos_;
};

} // namespace gfx_low
} // namespace ae
// EOF
