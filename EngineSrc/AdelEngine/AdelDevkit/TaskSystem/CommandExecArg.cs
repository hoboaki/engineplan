using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コマンド実行の際に渡す引数。
    /// </summary>
    public class CommandExecArg
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public CommandExecArg(Logger aLogger)
        {
            _Logger = aLogger;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログ出力用オブジェクト。
        /// </summary>
        public Logger Logger { get; }
        Logger _Logger;
    }
}
