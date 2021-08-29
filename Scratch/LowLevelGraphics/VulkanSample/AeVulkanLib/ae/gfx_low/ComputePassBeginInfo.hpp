// 文字コード：UTF-8
#pragma once

#include <ae/base/Aabb2i.hpp>
#include <ae/base/Pointer.hpp>

namespace ae {
namespace gfx_low {} // namespace gfx_low
} // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// BeginComputePass 関数実行に必要な情報。
/// @todo MTLDispatchType に相当するプロパティの対応。
class ComputePassBeginInfo {
public:
    /// @name プロパティ
    //@{
    //@}

private:
    int dummmy_ = {};
};

} // namespace gfx_low
} // namespace ae

// EOF
