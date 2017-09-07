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
            _NextCommandCtrls = new List<CommandCtrl>();
            _ExecutingCommandCtrls = new List<CommandCtrl>();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの追加。
        /// </summary>
        public void Add(TaskOld aTask)
        {
            // TaskNode化していく
            Action<CommandCtrl> commandCtrlAddCallback = (CommandCtrl aCommandCtrl) =>
            {
                _NextCommandCtrls.Add(aCommandCtrl);
            };
            _TaskNodes.Add(new TaskNode(aTask, commandCtrlAddCallback));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの更新。
        /// </summary>
        public void Update()
        {
            // Prepared になっているものを順番に実行していく
            int parallelCount = 1;
            foreach (var cmd in _NextCommandCtrls.ToArray())
            {
                if (cmd.State == TaskState.Prepared)
                {
                    _NextCommandCtrls.Remove(cmd);
                    _ExecutingCommandCtrls.Add(cmd);
                    if (_ExecutingCommandCtrls.Count == parallelCount)
                    {
                        break;
                    }
                }
            }
        }

        //------------------------------------------------------------------------------
        List<TaskNode> _TaskNodes;
        List<CommandCtrl> _NextCommandCtrls;
        List<CommandCtrl> _ExecutingCommandCtrls;
    }
}
