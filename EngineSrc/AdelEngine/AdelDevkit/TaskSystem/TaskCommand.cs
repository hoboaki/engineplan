using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの処理の実体。
    /// </summary>
    public class TaskCommand
    {
        /// <summary>
        /// コマンドの作成。
        /// </summary>
        public TaskCommand(Action<TaskCommandExecArg> aAction)
        {
            _Action = aAction;
        }

        /// <summary>
        /// コマンドの実行。
        /// </summary>
        public void Exec(TaskCommandExecArg aArg)
        {
            _Action(aArg);
        }

        Action<TaskCommandExecArg> _Action;
    }
}
