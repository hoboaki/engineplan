// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/QueuePriority.hpp>
#include <ae/gfx_low/QueueType.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Queue 作成情報。
class QueueCreateInfo {
public:
    /// @name Queue の種類（初期値：Normal）
    //@{
    QueueType Type() const { return type_; }
    QueueCreateInfo& SetType(QueueType type);
    //@}

    /// @name Queue の実行優先度（初期値：Normal）
    //@{
    QueuePriority Priority() const { return priority_; }
    QueueCreateInfo& SetPriority(QueuePriority priority);
    //@}

private:
    QueueType type_ = QueueType::Normal;
    QueuePriority priority_ = QueuePriority::Normal;
};

}  // namespace gfx_low

}  // namespace ae
// EOF
