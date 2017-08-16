using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの種類。
    /// </summary>
    public enum TaskKind
    {
        /// <summary>
        /// １つのコマンドを実行するタスク。
        /// </summary>
        Single,

        /// <summary>
        /// 複数のタスクを順次実行するタスク。
        /// </summary>
        MultiSerial,

        /// <summary>
        /// 複数のタスクを並列実行するタスク。
        /// </summary>
        MultiParallel,
    }
}
