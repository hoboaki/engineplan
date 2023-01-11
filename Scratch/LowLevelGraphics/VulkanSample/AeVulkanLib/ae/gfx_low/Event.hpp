// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/SdkHeader.hpp>

namespace ae::gfx_low {
class Device;
class EventCreateInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// GPU 内での同期を実現するクラス。
/// @details
/// Event は GPU 内での同期を実現する際に使うクラスで、主に複数 Queue
/// 間での同期に使われます。 Queue::PushEventSignal() と Queue::PushEventWait()
/// の関数を使って同期処理を行います。
///
/// Wait は Signal を受信するまでこれ以降の処理は行わないことを表します。
/// Signal と Wait は１対１に対応しており、多対１や１対多には対応していません。
/// もしそのような必要がある場合は複数の Event
/// オブジェクトを使って実現してください。
class Event {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Event(const EventCreateInfo& createInfo);
    ~Event();
    //@}

    /// @name プロパティ
    //@{
    /// 所属する Device。
    gfx_low::Device& Device() const { return device_; }
    //@}

    /// @name 内部処理用機能
    //@{
    ::vk::Semaphore& NativeObject_() { return nativeObject_; }
    //@}

private:
    gfx_low::Device& device_;
    ::vk::Semaphore nativeObject_;
};

} // namespace ae::gfx_low
// EOF
