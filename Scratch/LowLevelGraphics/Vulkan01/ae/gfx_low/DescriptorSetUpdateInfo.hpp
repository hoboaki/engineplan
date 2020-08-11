// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {
class UniformBufferDescriptorInfo;
}
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// DescriptorSet の更新時に使われる情報。
class DescriptorSetUpdateInfo {
public:
    /// @name プロパティ
    //@{
    /// UniformBuffer 用デスクリプタ情報の数。（初期値：0）
    int UniformBufferInfosCount() const { return uniformBufferInfosCount_; }

    /// UniformBuffer
    /// 用デスクリプタ情報がある配列の先頭アドレス。（初期値：nullptr）
    const UniformBufferDescriptorInfo* UniformBufferInfos() const {
        return uniformBufferInfos_.Get();
    }

    /// UniformBufferInfosCount() UniformBufferInfos() の設定。
    DescriptorSetUpdateInfo& SetUniformBufferInfos(
        int count, const UniformBufferDescriptorInfo* infos);
    //@}

private:
    int uniformBufferInfosCount_ = 0;
    base::Pointer<const UniformBufferDescriptorInfo> uniformBufferInfos_;
};

} // namespace gfx_low
} // namespace ae
// EOF
