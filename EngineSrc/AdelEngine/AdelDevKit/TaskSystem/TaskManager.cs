using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクを実行管理するクラス。
    /// </summary>
    public class TaskManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskManager()
        {
            _TaskNodes = new List<TaskNode>();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの追加。
        /// </summary>
        public void Add(Task aTask)
        {
            // TaskNode化していく
            _TaskNodes.Add(new TaskNode(aTask));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの更新。
        /// </summary>
        public void Update()
        {
            // Prepared になっているものを順番に実行していく
        }

        //------------------------------------------------------------------------------
        List<TaskNode> _TaskNodes;
    }
}
