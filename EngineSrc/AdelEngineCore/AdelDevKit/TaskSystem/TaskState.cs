using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの実行状態。
    /// </summary>
    public enum TaskState
    {
        /// <summary>
        /// 実行準備ができている状態。
        /// </summary>
        Prepared,

        /// <summary>
        /// 実行開始した状態。
        /// </summary>
        Executed,

        /// <summary>
        /// 実行が完了し成功した状態。
        /// </summary>
        Successed,

        /// <summary>
        /// 実行が完了し失敗した状態。
        /// </summary>
        Failed,

        /// <summary>
        /// キャンセルされた状態。
        /// </summary>
        Canceled,
    }
}
