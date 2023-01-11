// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/ShaderBindingStageBitSet.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ダイレクトコンスタントに関する情報。
class DirectConstantInfo {
public:
    /// @name プロパティ
    //@{
    /// 参照するシェーダーステージ郡。（初期値：AllOff()）
    ShaderBindingStageBitSet Stages() const { return stages_; }

    /// Stages() の設定。
    DirectConstantInfo& SetStages(const ShaderBindingStageBitSet& stages)
    {
        stages_ = stages;
        return *this;
    }

    /// データブロックサイズ。（初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定。
    DirectConstantInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }
    //@}

private:
    ShaderBindingStageBitSet stages_;
    size_t bindingIndex_ = 0;
    size_t size_ = 1;
};

} // namespace ae::gfx_low
// EOF
