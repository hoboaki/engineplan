using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの生成情報。
    /// </summary>
    public class TaskCreateInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aAction">処理内容。</param>
        public TaskCreateInfo(TaskAction aAction)
        {
            Action = aAction;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 処理の内容。
        /// </summary>
        public TaskAction Action { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 処理の名前。GUI上の表示などで使われる。
        /// </summary>
        public string Name { get; set; }
    }
}
