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
        /// 処理の名前。GUI上の表示などで使われる。
        /// </summary>
        public string Name { get; set; }
    }
}
