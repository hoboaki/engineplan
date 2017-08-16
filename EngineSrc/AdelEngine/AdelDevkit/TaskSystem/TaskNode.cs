using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
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
        public TaskNode(Task aTask, Action<CommandCtrl> aCommandCtrlCallback)
        {
            Task = aTask;

            switch (aTask.Kind)
            {
                case TaskKind.Single:
                    _CommandCtrl = new CommandCtrl(aTask.TaskCommand);
                    _CommandCtrl.PropertyChanged += CommandCtrl_PropertyChanged;
                    aCommandCtrlCallback(_CommandCtrl);
                    break;

                case TaskKind.MultiSerial:
                    {
                        // 子ノード作成
                        _Nodes = aTask.ChildTasks.Select(task =>
                        {
                            var newNode = new TaskNode(task, aCommandCtrlCallback);
                            newNode.PropertyChanged += ChildNode_PropertyChanged_ForSelfStateUpdate;
                            return newNode;
                        }).ToArray();

                        // １つ前のノードが完了したら次のノードをPrepareにするコールバックを登録
                        for (int i = 1; i < _Nodes.Length; ++i)
                        {
                            var prevNode = _Nodes[i - 1];
                            var nextNode = _Nodes[i];
                            PropertyChangedEventHandler eh = (sender, e) =>
                            {
                                if (e.PropertyName == nameof(TaskNode.State))
                                {
                                    switch (prevNode.State)
                                    {
                                        case TaskState.Successed:
                                            nextNode.Prepare();
                                            break;
                                    }
                                }
                            };
                            prevNode.PropertyChanged += eh;
                        }
                    }
                    break;

                case TaskKind.MultiParallel:
                    {
                        // 子ノード作成
                        _Nodes = aTask.ChildTasks.Select(task =>
                        {
                            var newNode = new TaskNode(task, aCommandCtrlCallback);
                            newNode.PropertyChanged += ChildNode_PropertyChanged_ForSelfStateUpdate;
                            return newNode;
                        }).ToArray();
                    }
                    break;
            }
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
                    case TaskState.Wait:
                        throw new InvalidOperationException();

                    case TaskState.Prepared:
                        // 待機状態以外からの呼び出しは不正
                        if (_State != TaskState.Wait)
                        {
                            throw new InvalidOperationException();
                        }
                        _State = value;

                        // 子に通知
                        switch (Task.Kind)
                        {
                            case TaskKind.Single:
                                _CommandCtrl.Prepare();
                                break;

                            case TaskKind.MultiSerial:
                                // 先頭だけ
                                _Nodes[0].Prepare();
                                break;

                            case TaskKind.MultiParallel:
                                // 全て
                                foreach (var node in _Nodes)
                                {
                                    node.Prepare();
                                }
                                break;
                        }
                        break;

                    case TaskState.Executed:
                        // 何もしない
                        _State = value;
                        break;

                    case TaskState.Successed:
                        // 何もしない
                        _State = value;
                        break;

                    case TaskState.Failed:
                        // 特定状態以外からの呼び出しは不正
                        if (_State != TaskState.Executed)
                        {
                            throw new InvalidOperationException();
                        }
                        _State = value;

                        // 子にキャンセル通知
                        switch (Task.Kind)
                        {
                            case TaskKind.Single:
                                break;

                            case TaskKind.MultiSerial:
                            case TaskKind.MultiParallel:
                                foreach (var node in _Nodes)
                                {
                                    node.Cancel();
                                }
                                break;
                        }
                        break;

                    case TaskState.Canceled:
                        // 特定状態以外からの呼び出しは不正
                        if (_State != TaskState.Wait && _State != TaskState.Prepared)
                        {
                            throw new InvalidOperationException();
                        }
                        _State = value;


                        // 子に通知
                        switch (Task.Kind)
                        {
                            case TaskKind.Single:
                                _CommandCtrl.Cancel();
                                break;

                            case TaskKind.MultiSerial:
                            case TaskKind.MultiParallel:
                                // 全て
                                foreach (var node in _Nodes)
                                {
                                    node.Cancel();
                                }
                                break;
                        }
                        break;
                }
            }
        }
        TaskState _State = TaskState.Wait;

        //------------------------------------------------------------------------------
        Task Task { get; set; }
        CommandCtrl _CommandCtrl;
        TaskNode[] _Nodes;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行準備状態にする。
        /// </summary>
        public void Prepare()
        {
            if (State == TaskState.Wait)
            {
                State = TaskState.Prepared;
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行をキャンセルする。
        /// </summary>
        public void Cancel()
        {
            switch (State)
            {
                case TaskState.Wait:
                case TaskState.Prepared:
                    State = TaskState.Canceled;
                    break;
            }
        }

        //------------------------------------------------------------------------------
        void CommandCtrl_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(CommandCtrl.State))
            {
                switch (_CommandCtrl.State)
                {
                    case TaskState.Prepared:
                        // 何もしない
                        break;

                    case TaskState.Executed:
                        // 自身に反映
                        State = TaskState.Executed;
                        break;

                    case TaskState.Successed:
                        // 自身に反映
                        State = TaskState.Successed;
                        break;

                    case TaskState.Failed:
                        // 自身に反映
                        State = TaskState.Failed;
                        break;

                    case TaskState.Canceled:
                        // 何もしない
                        break;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }

        //------------------------------------------------------------------------------
        void ChildNode_PropertyChanged_ForSelfStateUpdate(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(State))
            {
                switch (State)
                {
                    case TaskState.Prepared:
                        // 何もしない
                        break;

                    case TaskState.Executed:
                        // 自身に反映
                        State = TaskState.Executed;
                        break;

                    case TaskState.Successed:
                        // 自身に反映
                        State = TaskState.Successed;
                        break;

                    case TaskState.Failed:
                        // 自身に反映
                        State = TaskState.Failed;
                        break;

                    case TaskState.Canceled:
                        // 何もしない
                        break;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
    }
}
