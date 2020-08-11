// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/DescriptorKind.hpp>

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
    /// 指定のデスクリプタ種類のバインド情報の数。（初期値：0）
    int BindingInfoCount(DescriptorKind kind) const { 
        return infos_[kind].infoCount; 
    }

    /// 指定のデスクリプタ種類のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* BindingInfos(DescriptorKind kind) const {
        return infos_[kind].infos.Get();
    }

    /// BindingInfoCount() BindingInfos() の設定。
    /// @param count 0 以上。
    /// @infos count == 0 のときは nullptr を指定。それ以外のときは配列のポインタを指定。
    DescriptorSetSpecInfo& SetBindingInfos(DescriptorKind kind, int count,
        const ShaderBindingInfo* infosPtr = nullptr);

    /// 指定のデスクリプタ種類の総バインド数を計算して取得。（初期値：0）
    int TotalBindingCount(DescriptorKind kind) const;
    //@}

private:
    class DescriptorInfo
    {
    public:
        int infoCount = 0;
        base::Pointer<const ShaderBindingInfo> infos;
    };

    base::EnumKeyArray<DescriptorKind, DescriptorInfo> infos_;
};

} // namespace gfx_low
} // namespace ae
// EOF
