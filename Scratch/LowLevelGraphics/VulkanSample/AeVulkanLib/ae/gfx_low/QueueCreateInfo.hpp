// 文字コード：UTF-8
#pragma once

#include <ae/gfx_low/QueueKind.hpp>
#include <ae/gfx_low/QueuePriority.hpp>

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// Queue 作成情報。
class QueueCreateInfo {
public:
    /// @name プロパティ
    //@{
    /// Queue の種類。（初期値：Normal）
    QueueKind Kind() const { return type_; }

    /// Kind() の設定。
    QueueCreateInfo& SetKind(QueueKind type);

    /// Queue の実行優先度。（初期値：Normal）
    QueuePriority Priority() const { return priority_; }

    /// Priority() の設定。
    QueueCreateInfo& SetPriority(QueuePriority priority);

    /// Queue に詰める操作の最大数。（初期値：0）
    int OperationCountMax() const { return operationCountMax_; }

    /// OperationCountMax() の設定。
    /// @param operationCountMax [0, operationCountMax]
    QueueCreateInfo& SetOperationCountMax(int operationCountMax);
    //@}

private:
    QueueKind type_ = QueueKind::Normal;
    QueuePriority priority_ = QueuePriority::Normal;
    int operationCountMax_ = 0;
};

} // namespace ae::gfx_low
// EOF
