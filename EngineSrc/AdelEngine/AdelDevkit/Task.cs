using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk
{
    public class TaskCommandExecArg
    {
        public TaskCommandExecArg(Logger aLogger)
        {
            _Logger = aLogger;
        }

        public Logger Logger { get; }
        Logger _Logger;
    }

    public class TaskCommand
    {
        public TaskCommand(Action<TaskCommandExecArg> aAction)
        {
            _Action = aAction;
        }

        public void Exec(TaskCommandExecArg aArg)
        {
            _Action(aArg);
        }

        Action<TaskCommandExecArg> _Action;
    }
    
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの種類。
    /// </summary>
    public enum TaskKind
    {
        /// <summary>
        /// １つのコマンドを実行するタスク。
        /// </summary>
        Single,

        /// <summary>
        /// 複数のタスクを順次実行するタスク。
        /// </summary>
        MultiSerial,

        /// <summary>
        /// 複数のタスクを並列実行するタスク。
        /// </summary>
        MultiParallel,
    }

    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの生成情報。
    /// </summary>
    public class TaskCreateInfo
    {
        /// <summary>
        /// 処理の名前。GUI上の表示などで使われる。
        /// </summary>
        public string Name { get; set; }
    }

    //------------------------------------------------------------------------------
    /// <summary>
    /// １つの処理セットを表すクラス。
    /// </summary>
    public class Task
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// １つのコマンドを実行するタスクとして作成。
        /// </summary>
        static public Task CreateSingle(TaskCommand aCommand, TaskCreateInfo aCreateInfo)
        {
            var obj = new Task();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.Single;
            obj._TaskCommand = aCommand;
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 複数のタスク項目を順次実行するタスクとして作成。
        /// </summary>
        static public Task CreateMultiSerial(IEnumerable<Task> aChildTasks, TaskCreateInfo aCreateInfo)
        {
            var obj = new Task();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.MultiSerial;
            obj._ChildTasks = aChildTasks.ToArray();
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 複数のタスク項目を並列実行するタスクとして作成。
        /// </summary>
        static public Task CreateMultiParallel(IEnumerable<Task> aChildTasks, TaskCreateInfo aCreateInfo)
        {
            var obj = new Task();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.MultiParallel;
            obj._ChildTasks = aChildTasks.ToArray();
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 作成時に渡した情報。
        /// </summary>
        public TaskCreateInfo CreateInfo { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの種類。
        /// </summary>
        public TaskKind Kind { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CreateSingle で指定したコマンド。
        /// </summary>
        public TaskCommand TaskCommand
        {
            get
            {
                switch (Kind)
                {
                    case TaskKind.Single:
                        return _TaskCommand;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
        TaskCommand _TaskCommand = null;

        //------------------------------------------------------------------------------
        /// <summary>
        /// CreateMultiSingle CreateMultiParallel で指定した子タスク。
        /// </summary>
        public Task[] ChildTasks
        {
            get
            {
                switch (Kind)
                {
                    case TaskKind.MultiSerial:
                    case TaskKind.MultiParallel:
                        return _ChildTasks;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
        Task[] _ChildTasks = null;
    }
    
    //------------------------------------------------------------------------------
    public class TaskNode : Livet.NotificationObject
    {
        //------------------------------------------------------------------------------
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
                                foreach (var node in _Nodes) {
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
        public void Prepare()
        {
            if (State == TaskNodeState.Wait)
            {
                State = TaskNodeState.Prepared;
            }
        }

        //------------------------------------------------------------------------------
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
        void CommandCtrl_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
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
        void ChildNode_PropertyChanged_ForSelfStateUpdate(object sender, System.ComponentModel.PropertyChangedEventArgs e)
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
    
    public enum TaskNodeState
    {
        Wait,
        Prepared,
        Executed,
        Finished,
        Canceled,
    }

    public class TaskCommandCtrl : Livet.NotificationObject
    {
        public TaskCommandCtrl(TaskCommand aCommand)
        {
            Command = aCommand;
        }

        public TaskCommand Command { get; private set; }

        public TaskNodeState State
        {
            get
            {
                return _State;
            }
            set
            {
                if (_State != value)
                {
                    _State = value;
                    RaisePropertyChanged(nameof(State));
                }
            }

        }
        TaskNodeState _State = TaskNodeState.Wait;

        public void Prepare()
        {
            if (_State == TaskNodeState.Wait)
            {
                State = TaskNodeState.Prepared;
            }
        }
        
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
    }

    public class TaskManager
    {
        public TaskManager()
        {
            _TasksCommandCtrls = new List<TaskCommandCtrl>();
        }

        public void Add(Task aTask)
        {
            // TaskNode化していく

        }

        public void Update()
        {
            // Prepared になっているものを順番に実行していく
            // ...
        }

        List<TaskCommandCtrl> _TasksCommandCtrls;
    }

}
