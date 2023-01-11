// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class SamplerDescriptorInfo;
class SampledImageDescriptorInfo;
class StorageBufferDescriptorInfo;
class StorageImageDescriptorInfo;
class UniformBufferDescriptorInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// DescriptorSet の更新時に使われる情報。
class DescriptorSetUpdateInfo {
public:
    /// @name プロパティ
    //@{
    /// UniformBuffer 用デスクリプタ情報の数。（初期値：0）
    int UniformBufferInfoCount() const { return uniformBufferInfoCount_; }

    /// UniformBuffer
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const UniformBufferDescriptorInfo* UniformBufferInfos() const
    {
        return uniformBufferInfos_.Get();
    }

    /// UniformBufferInfoCount() UniformBufferInfos() の設定。
    DescriptorSetUpdateInfo& SetUniformBufferInfos(
        int count,
        const UniformBufferDescriptorInfo* infos);

    /// StorageBuffer 用デスクリプタ情報の数。（初期値：0）
    int StorageBufferInfoCount() const { return storageBufferInfoCount_; }

    /// StorageBuffer
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const StorageBufferDescriptorInfo* StorageBufferInfos() const
    {
        return storageBufferInfos_.Get();
    }

    /// StorageBufferInfoCount() StorageBufferInfos() の設定。
    DescriptorSetUpdateInfo& SetStorageBufferInfos(
        int count,
        const StorageBufferDescriptorInfo* infos);

    /// SampledImage 用デスクリプタ情報の数。（初期値：0）
    int SampledImageInfoCount() const { return sampledImageInfoCount_; }

    /// SampledImage
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const SampledImageDescriptorInfo* SampledImageInfos() const
    {
        return sampledImageInfos_.Get();
    }

    /// SampledImageInfoCount() SampledImageInfos() の設定。
    DescriptorSetUpdateInfo& SetSampledImageInfos(
        int count,
        const SampledImageDescriptorInfo* infos);

    /// StorageImage 用デスクリプタ情報の数。（初期値：0）
    int StorageImageInfoCount() const { return storageImageInfoCount_; }

    /// StorageImage
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const StorageImageDescriptorInfo* StorageImageInfos() const
    {
        return storageImageInfos_.Get();
    }

    /// StorageImageInfoCount() StorageImageInfos() の設定。
    DescriptorSetUpdateInfo& SetStorageImageInfos(
        int count,
        const StorageImageDescriptorInfo* infos);

    /// Sampler 用デスクリプタ情報の数。（初期値：0）
    int SamplerInfoCount() const { return samplerInfoCount_; }

    /// Sampler
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const SamplerDescriptorInfo* SamplerInfos() const
    {
        return samplerInfos_.Get();
    }

    /// SamplerInfoCount() SamplerInfos() の設定。
    DescriptorSetUpdateInfo& SetSamplerInfos(
        int count,
        const SamplerDescriptorInfo* infos);

    //@}

private:
    int uniformBufferInfoCount_ = 0;
    int storageBufferInfoCount_ = 0;
    int sampledImageInfoCount_ = 0;
    int storageImageInfoCount_ = 0;
    int samplerInfoCount_ = 0;
    base::Pointer<const UniformBufferDescriptorInfo> uniformBufferInfos_;
    base::Pointer<const StorageBufferDescriptorInfo> storageBufferInfos_;
    base::Pointer<const SampledImageDescriptorInfo> sampledImageInfos_;
    base::Pointer<const StorageImageDescriptorInfo> storageImageInfos_;
    base::Pointer<const SamplerDescriptorInfo> samplerInfos_;
};

} // namespace ae::gfx_low
// EOF
