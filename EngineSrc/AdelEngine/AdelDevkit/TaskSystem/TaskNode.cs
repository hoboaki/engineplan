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
        public TaskNode(Task aTask)
        {
            Task = aTask;

            switch (aTask.Kind)
            {
                case TaskKind.Single:
                    _CommandCtrl = new TaskCommandCtrl(aTask.TaskCommand);
                    _CommandCtrl.PropertyChanged += CommandCtrl_PropertyChanged;
                    break;

                case TaskKind.MultiSerial:
                    {
                        // 子ノード作成
                        _Nodes = aTask.ChildTasks.Select(task =>
                        {
                            var newNode = new TaskNode(task);
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
                                        case TaskNodeState.Finished:
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
                            var newNode = new TaskNode(task);
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
        public TaskNodeState State
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
                    case TaskNodeState.Wait:
                        throw new InvalidOperationException();

                    case TaskNodeState.Prepared:
                        // 待機状態以外からの呼び出しは不正
                        if (_State != TaskNodeState.Wait)
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

                    case TaskNodeState.Executed:
                        // 何もしない
                        break;

                    case TaskNodeState.Finished:
                        // 何もしない
                        break;

                    case TaskNodeState.Canceled:
                        // 特定状態以外からの呼び出しは不正
                        if (_State == TaskNodeState.Wait || _State == TaskNodeState.Prepared)
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
        TaskNodeState _State = TaskNodeState.Wait;

        //------------------------------------------------------------------------------
        Task Task { get; set; }
        TaskCommandCtrl _CommandCtrl;
        TaskNode[] _Nodes;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行準備状態にする。
        /// </summary>
        public void Prepare()
        {
            if (State == TaskNodeState.Wait)
            {
                State = TaskNodeState.Prepared;
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
                case TaskNodeState.Wait:
                case TaskNodeState.Prepared:
                    State = TaskNodeState.Canceled;
                    break;
            }
        }

        //------------------------------------------------------------------------------
        void CommandCtrl_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(TaskCommandCtrl.State))
            {
                switch (_CommandCtrl.State)
                {
                    case TaskNodeState.Prepared:
                        // 何もしない
                        break;

                    case TaskNodeState.Executed:
                        // 自身に反映
                        State = TaskNodeState.Executed;
                        break;

                    case TaskNodeState.Finished:
                        // 自身に反映
                        State = TaskNodeState.Finished;
                        break;

                    case TaskNodeState.Canceled:
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
                    case TaskNodeState.Prepared:
                        // 何もしない
                        break;

                    case TaskNodeState.Executed:
                        // 自身に反映
                        State = TaskNodeState.Executed;
                        break;

                    case TaskNodeState.Finished:
                        // 自身に反映
                        State = TaskNodeState.Finished;
                        break;

                    case TaskNodeState.Canceled:
                        // 何もしない
                        break;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
    }
}
