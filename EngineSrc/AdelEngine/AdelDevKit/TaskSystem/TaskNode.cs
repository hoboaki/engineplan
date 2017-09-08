using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// １つのタスクを扱う制御クラス。
    /// </summary>
    public class TaskNode : Livet.NotificationObject
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary
        public TaskNode(Task aTask)
        {
            Task = aTask;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの状態。
        /// </summary>
        public TaskState State
        {
            get
            {
                return _State;
            }
            private set
            {
                if (_State == value)
                {
                    return;
                }
                switch (value)
                {
                    case TaskState.Executed:
                        // 何もしない
                        _State = value;
                        RaisePropertyChanged(nameof(State));
                        break;

                    case TaskState.Successed:
                        // 何もしない
                        _State = value;
                        RaisePropertyChanged(nameof(State));
                        break;

                    case TaskState.Failed:
                        // 特定状態以外からの呼び出しは不正
                        if (_State != TaskState.Executed)
                        {
                            throw new InvalidOperationException();
                        }
                        _State = value;
                        RaisePropertyChanged(nameof(State));

                        // 子にキャンセル通知
                        foreach (var node in _PreparedNodes.ToArray())
                        {
                            node.Cancel();
                        }
                        break;

                    case TaskState.Canceled:
                        // 特定状態以外からの呼び出しは不正
                        switch (_State)
                        {
                            case TaskState.Prepared:
                                break;

                            default:
                                throw new InvalidOperationException();
                        }
                        _State = value;
                        RaisePropertyChanged(nameof(State));

                        // 子に通知
                        foreach (var node in _PreparedNodes.ToArray())
                        {
                            node.Cancel();
                        }
                        break;
                }
            }
        }
        TaskState _State = TaskState.Prepared;

        //------------------------------------------------------------------------------
        Task Task { get; set; }
        List<TaskNode> _PreparedNodes = new List<TaskNode>();
        List<TaskNode> _ExecutedNodes = new List<TaskNode>(); // 実行もしくはキャンセルされたらこちらに移動する。

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行をキャンセルする。
        /// </summary>
        public void Cancel()
        {
            switch (State)
            {
                case TaskState.Prepared:
                    State = TaskState.Canceled;
                    break;
            }
        }
    }
}
