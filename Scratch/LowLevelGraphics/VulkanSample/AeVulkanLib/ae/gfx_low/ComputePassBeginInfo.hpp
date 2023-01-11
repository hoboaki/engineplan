// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// BeginComputePass 関数実行に必要な情報。
/// @todo MTLDispatchType に相当するプロパティの対応。
class ComputePassBeginInfo {
public:
    /// @name プロパティ
    //@{
    /// セカンダリコマンドバッファを使用するか。（初期値：false）
    /// @details
    /// true の場合、このコンピュートパス内において全てのコマンドは
    /// セカンダリコマンドバッファによって実行する必要があります。
    bool UseSecondaryCommandBuffers() const
    {
        return useSecondaryCommandBuffers_;
    }

    /// UseSecondaryCommandBuffers() の設定。
    ComputePassBeginInfo& SetUseSecondaryCommandBuffers(bool use)
    {
        useSecondaryCommandBuffers_ = use;
        return *this;
    }
    //@}

private:
    bool useSecondaryCommandBuffers_ = false;
};

} // namespace ae::gfx_low

// EOF
