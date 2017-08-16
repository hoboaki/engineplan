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
    public class Command
    {
        /// <summary>
        /// コマンドの作成。
        /// </summary>
        public Command(Action<CommandExecArg> aAction)
        {
            _Action = aAction;
        }

        /// <summary>
        /// コマンドの実行。
        /// </summary>
        public void Exec(CommandExecArg aArg)
        {
            _Action(aArg);
        }

        Action<CommandExecArg> _Action;
    }
}
