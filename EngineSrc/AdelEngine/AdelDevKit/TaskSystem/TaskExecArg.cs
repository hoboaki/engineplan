using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コマンド実行の際に渡す引数。
    /// </summary>
    public class TaskExecArg
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskExecArg(Logger aLogger)
        {
            _Logger = aLogger;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログ出力用オブジェクト。
        /// </summary>
        public Logger Logger { get { return _Logger; } }
        Logger _Logger;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクを追加し非同期に処理を開始する。
        /// </summary>
        /// <remarks>
        /// 開始した処理の終了を待つには <see cref="WaitAllChildTaskDone"/> を呼ぶこと。
        /// </remarks>
        public void ExecChildTaskAsync(Task aTask)
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 全ての子タスクが終了するのを待つ。
        /// </summary>
        public void WaitAllChildTaskDone()
        {
        }
    }
}
