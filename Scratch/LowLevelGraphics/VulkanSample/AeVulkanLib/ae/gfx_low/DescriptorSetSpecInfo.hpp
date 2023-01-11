// 文字コード：UTF-8
#pragma once

#include <ae/base/EnumKeyArray.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/DescriptorKind.hpp>

namespace ae::gfx_low {
class DirectConstantInfo;
class ShaderBindingInfo;
;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// DescriptorSet の仕様情報。
/// @details
/// BindingInfos() のインデックスをバインド番号として扱います。
/// 各プラットフォーム毎のバインド番号の仕様・制約は以下の通りです。
///
/// **VK-GLSL**
/// - buffer(storage) のシェーダーコード上バインド番号は buffer(uniform) の最大番号 + 1 からスタート。
/// - image(write) のシェーダーコード上バインド番号は image(read)の最大番号 + 1 からスタート。
///
/// **MSL**
/// - 通常 buffer(storage) のシェーダーコード上バインド番号は buffer(uniform) の最大番号 + 1 からスタート。
///   ただし、ダイレクトコンスタントを使う場合は buffer(uniform) の最大番号 + 1 が
///   ダイレクトコンスタントに割り当てられる。その場合は buffer(storage) の
///   シェーダーコード上バインド番号は buffer(uniform) の最大番号 + 2 からスタートさせること。
/// - image(write) のシェーダーコード上バインド番号は image(read)の最大番号 + 1 からスタート。
///
/// **HLSL**
/// - ダイレクトコンスタントのバインド番号は buffer(uniform) の最大番号 + 1 を割り当てる。
/// - image(write) のシェーダーコード上バインド番号は buffer(storage)の最大番号 + 1 からスタート。
///
/// 例えば VK-GLSL 環境において UniformBuffer が3つ、StorageBuffer を2つ使う場合、
/// シェーダーコード上では buffer(uniform) の番号を 0,1,2 に割り当て、
/// buffer(storage) を buffer(uniform) の最大番号のプラス1スタートで 3,4 を割り当ててください。
/// そしてこの場合、 本クラス DescriptorSetSpecInfo::BindingInfos() の
/// kind == UniformBuffer における BindingInfos のインデックス 0 番は buffer(uniform) の 0 番を指し、
/// kind == StorageBuffer のインデックス 0 番は storage の 0 番目であるバインド番号 3 の buffer(storage) を指します。
///
/// また、VK-GLSL 環境では DescriptorSet 番号を Buffer, Image, Sampler の順番で DescriptorSet 番号を 0 から順番に割り当ててください。
/// Buffer を使わず Image ＆ Sampler だけ使うといった場合は Image に set=0、Sampler に set=1 を割り当ててください。
///
///
/// ダイレクトコンスタントは１シェーダーステージにつき１つまでしか割り当てることはできません。
/// またダイレクトコンスタントの扱えるサイズは実行環境によって異なります。
/// 推奨としては全ダイレクトコンスタントの合計サイズが 128 以下とします。
class DescriptorSetSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// 指定のデスクリプタ種類のバインド情報の数。（初期値：0）
    int BindingInfoCount(DescriptorKind kind) const
    {
        return bindingInfos_[kind].infoCount;
    }

    /// 指定のデスクリプタ種類のバインド情報郡。（初期値：nullptr）
    const ShaderBindingInfo* BindingInfos(DescriptorKind kind) const
    {
        return bindingInfos_[kind].infos.Get();
    }

    /// BindingInfoCount() BindingInfos() の設定。
    /// @param count 0 以上。
    /// @param infos count == 0 のときは nullptr を指定。それ以外のときは配列のポインタを指定。
    /// バインドに関する制約についてはクラスコメントを参照してください。
    DescriptorSetSpecInfo& SetBindingInfos(
        DescriptorKind kind,
        int count,
        const ShaderBindingInfo* infosPtr = nullptr);

    /// 指定のデスクリプタ種類の総バインド数を計算して取得。（初期値：0）
    /// @details
    /// ここにダイレクトコンスタントデータは含まれていません。
    int TotalBindingCount(DescriptorKind kind) const;

    /// 指定のデスクリプタ種類の最大バインディング番号を取得。
    /// @details 該当するでスクリプタが１つもないときは負の値を返します。
    int MaxBindingIndex(DescriptorKind kind) const;

    /// ダイレクトコンスタント情報の数。（初期値：0）
    int DirectConstantInfoCount() const { return directConstantInfoCount_; }

    /// ダイレクトコンスタントの情報群。（初期値：nullptr）
    const DirectConstantInfo* DirectConstantInfos() const
    {
        return directConstantInfos_.Get();
    }

    /// DirectConstantCount() DirectConstantInfos() の設定。
    /// @param count 0 以上。
    /// @param infos count == 0 のときは nullptr を指定。それ以外のときは配列のポインタを指定。
    /// @details
    /// ダイレクトコンスタントに関する制約についてはクラスコメントを参照してください。
    DescriptorSetSpecInfo& SetDirectConstantInfos(
        int count,
        const DirectConstantInfo* infosPtr = nullptr);
    //@}

    /// @name 内部処理用機能
    //@{
    /// 内容が問題ないか確認する。
    void Validate_() const;
    //@}

private:
    class DescriptorInfo {
    public:
        int infoCount = 0;
        base::Pointer<const ShaderBindingInfo> infos;
    };

    int directConstantInfoCount_ = 0;
    base::EnumKeyArray<DescriptorKind, DescriptorInfo> bindingInfos_;
    base::Pointer<const DirectConstantInfo> directConstantInfos_;
};

} // namespace ae::gfx_low
// EOF
