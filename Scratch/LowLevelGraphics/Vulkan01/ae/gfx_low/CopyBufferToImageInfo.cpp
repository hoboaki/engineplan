// 文字コード：UTF-8
#include <ae/gfx_low/CopyBufferToImageInfo.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

//------------------------------------------------------------------------------
CopyBufferToImageInfo& CopyBufferToImageInfo::SetDstImageResourceState(
    const ImageResourceState state) {
    AE_BASE_ASSERT_ENUM(state, ImageResourceState);

    // 現時点では TransferDstOptimal のみサポート
    AE_BASE_ASSERT(state == ImageResourceState::TransferDstOptimal);
    dstImageResourceState_ = state;
    return *this;
}

} // namespace gfx_low
} // namespace ae
// EOF
