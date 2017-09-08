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
        /// 子タスク実行関数。
        /// </summary>
        internal delegate void ExecChildTaskFunc(Task aTask);

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスク終了待機関数。
        /// </summary>
        internal delegate void WaitAllChildTaskDoneFunc();

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal TaskExecArg(Logger aLogger, ExecChildTaskFunc aExecChildTaskFunc, WaitAllChildTaskDoneFunc aWaitAllChildTaskDoneFunc)
        {
            if (aLogger == null)
            {
                throw new ArgumentNullException(nameof(aLogger));
            }
            if (aExecChildTaskFunc == null)
            {
                throw new ArgumentNullException(nameof(aExecChildTaskFunc));
            }
            if (aWaitAllChildTaskDoneFunc == null)
            {
                throw new ArgumentNullException(nameof(aWaitAllChildTaskDoneFunc));
            }

            _Logger = aLogger;
            _ExecChildTaskFunc = aExecChildTaskFunc;
            _WaitAllChildTaskDoneFunc = aWaitAllChildTaskDoneFunc;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログ出力用オブジェクト。
        /// </summary>
        public Logger Logger { get { return _Logger; } }
        Logger _Logger;

        //------------------------------------------------------------------------------
        ExecChildTaskFunc _ExecChildTaskFunc;
        WaitAllChildTaskDoneFunc _WaitAllChildTaskDoneFunc;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクを追加し非同期に処理を開始する。
        /// </summary>
        /// <remarks>
        /// 開始した処理の終了を待つには <see cref="WaitAllChildTaskDone"/> を呼ぶこと。
        /// </remarks>
        public void ExecChildTaskAsync(Task aTask)
        {
            _ExecChildTaskFunc(aTask);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 全ての子タスクが終了するのを待つ。
        /// </summary>
        public void WaitAllChildTaskDone()
        {
            _WaitAllChildTaskDoneFunc();
        }
    }
}
