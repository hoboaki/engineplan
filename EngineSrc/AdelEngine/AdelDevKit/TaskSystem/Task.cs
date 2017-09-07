using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスク。
    /// </summary>
    public class Task
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コマンドの作成。
        /// </summary>
        public Task(TaskCreateInfo aCreateInfo)
        {
            CreateInfo = aCreateInfo;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 作成情報。
        /// </summary>
        public TaskCreateInfo CreateInfo { get; private set; }
    }
}
