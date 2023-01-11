// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class FenceCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CPU & GPU 間での同期を実現するクラス。
/// @details
/// Fence は GPU のタイミングを CPU 上で待つ同期を実現する際に使うクラスです。
/// Queue::Submit() の引数で渡した後、Wait()
/// を呼ぶことによって同期処理を行います。
///
/// Queue::Submit() に渡した Fence は Wait() しないまま Queue::Submit()
/// することはできません。 その場合、必ず Wait() をしてください。
class Fence {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Fence(const FenceCreateInfo& createInfo);
    ~Fence();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 同期
    //@{
    /// GPU からシグナルがくるまで待つ。
    /// @details
    /// Submit していない状態ではすぐに処理が戻ります。
    void Wait();

    // @todo タイムアウト付きの TryToWait() の実装。
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Fence& NativeObject_() { return nativeObject_; }

    /// Submit 時に呼ぶ処理。
    void OnSubmit_();
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Fence nativeObject_;
    bool isActive_ = false;
};

} // namespace ae::gfx_low
// EOF
