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
/// @details
/// BindingInfos() のインデックスをバインド番号として扱います。
/// 各プラットフォーム毎のバインド番号の仕様・制約は以下の通りです。
/// 
/// - VK-GLSL と MSL において buffer(storage) のシェーダーコード上バインド番号は buffer(uniform) の最大番号 + 1 からスタート。
/// - VK-GLSL と MSL において image(write) のシェーダーコード上バインド番号は image(read)の最大番号 + 1 からスタート。
/// - HLSL において image(write) のシェーダーコード上バインド番号は buffer(storage)の最大番号 + 1 からスタート。 
/// 
/// 例えば VK-GLSL 環境において UniformBuffer が3つ、StorageBuffer を2つ使う場合、
/// シェーダーコード上では buffer(uniform) の番号を 0,1,2 に割り当て、
/// buffer(storage) を buffer(uniform) の最大番号のプラス1スタートで 3,4 を割り当ててください。
/// そしてこの場合、 本クラス DescriptorSetSpecInfo::BindingInfos() の
/// kind == UniformBuffer における BindingInfos のインデックス 0 番は buffer(uniform) の 0 番を指し、
/// kind == StorageBuffer のインデックス 0 番は storage の 0 番目であるバインド番号 3 の buffer(storage) を指します。
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
    DescriptorSetSpecInfo& SetBindingInfos(
        DescriptorKind kind,
        int count,
        const ShaderBindingInfo* infosPtr = nullptr);

    /// 指定のデスクリプタ種類の総バインド数を計算して取得。（初期値：0）
    int TotalBindingCount(DescriptorKind kind) const;
    //@}

private:
    class DescriptorInfo {
    public:
        int infoCount = 0;
        base::Pointer<const ShaderBindingInfo> infos;
    };

    base::EnumKeyArray<DescriptorKind, DescriptorInfo> infos_;
};

} // namespace gfx_low
} // namespace ae
// EOF
