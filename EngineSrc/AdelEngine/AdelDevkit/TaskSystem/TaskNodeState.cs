using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクノードの状態。
    /// </summary>
    public enum TaskNodeState
    {
        /// <summary>
        /// 待機中でまだ実行できない状態。
        /// </summary>
        Wait,

        /// <summary>
        /// 実行準備ができている状態。
        /// </summary>
        Prepared,

        /// <summary>
        /// 実行開始した状態。
        /// </summary>
        Executed,

        /// <summary>
        /// 実行が完了した状態。
        /// </summary>
        Finished,

        /// <summary>
        /// キャンセルされた状態。
        /// </summary>
        Canceled,
    }
}
