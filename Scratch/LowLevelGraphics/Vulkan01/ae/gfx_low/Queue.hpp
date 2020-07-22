// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/base/PtrToRef.hpp>
#include <ae/gfx_low/QueueType.hpp>
#include <ae/gfx_low/SdkHeader.hpp>

namespace ae {
namespace gfx_low {
class Device;
}
}  // namespace ae

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// キューを扱うクラス。
/// @details
/// キューはグラフィックスデバイスへのコマンドの送信やスワップチェインへの転送機能などを提供します。
/// キューに対する操作は順番に蓄積され、 Flush()
/// が呼ばれたタイミングで蓄積済の操作の実行を開始します。
///
/// キューの作成は Device と一緒に作成されます。
/// 作成されたキューは Device::Queue() で取得できます。
class Queue {
public:
    /// @name プロパティ
    //@{
    /// 所属する Device。
    Device& device() const { return device_; }

    /// Queue の種類。
    QueueType Type() const { return type_; }
    //@}

    /// @name 内部処理用機能
    //@{
    /// 内部処理用コンストラクタ。アプリケーション側からの呼び出しは禁止。
    Queue(Device* device, const ::vk::Queue& queue, QueueType type)
    : device_(base::PtrToRef(device))
    , queue_(queue)
    , type_(type) {}

    ::vk::Queue InternalInstance() const { return queue_; }
    //@}

private:
    Device& device_;
    ::vk::Queue queue_;
    QueueType type_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
