// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ImageResourceState.hpp>
#include <ae/gfx_low/ImageSubresourceLocation.hpp>

namespace ae::gfx_low {
class ImageResource;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ImageResource のバリアフェンス設定に関する情報。
class ImageResourceBarrierInfo {
public:
    /// @name プロパティ
    //@{
    /// 対象となるイメージリソース。（初期値：nullptr）
    ImageResource* Resource() const { return resource_.Get(); }

    /// Resource() の設定。（設定必須）
    ImageResourceBarrierInfo& SetResource(ImageResource* resource)
    {
        resource_.Reset(resource);
        return *this;
    }

    /// 遷移前の状態。（初期値：Invalid）
    ImageResourceState OldState() const { return newState_; }

    /// OldState() の設定。（設定必須）
    ImageResourceBarrierInfo& SetOldState(ImageResourceState state);

    /// 遷移後の状態。（初期値：Invalid）
    ImageResourceState NewState() const { return oldState_; }

    /// NewState() の設定。（設定必須）
    ImageResourceBarrierInfo& SetNewState(ImageResourceState state);

    /// 特定のサブリソースのみバリアフェンスを設定するか。（初期値：false）
    /// @details false の場合は全サブリソースに対してバリアフェンスを設定する。
    bool IsSubresourceSpecified() const { return isSubresourceSpecified_; }

    /// IsSubresourceSpecified() の設定。
    ImageResourceBarrierInfo& SetIsSubresourceSpecified(bool isSpecified)
    {
        isSubresourceSpecified_ = isSpecified;
        return *this;
    }

    /// 特定サブリソース指定する場合の対象となるサブリソース。（初期値：デフォルトコンストラクタの値）
    ImageSubresourceLocation SubresourceLocation() const
    {
        return subresourceLocation_;
    }

    /// SubresourceLocation() の設定。
    ImageResourceBarrierInfo& SetSubresourceLocation(
        const ImageSubresourceLocation& location)
    {
        subresourceLocation_ = location;
        return *this;
    }
    //@]

private:
    base::Pointer<ImageResource> resource_;
    ImageResourceState newState_ = ImageResourceState::Invalid;
    ImageResourceState oldState_ = ImageResourceState::Invalid;
    ImageSubresourceLocation subresourceLocation_;
    bool isSubresourceSpecified_ = false;
};

} // namespace ae::gfx_low
// EOF
