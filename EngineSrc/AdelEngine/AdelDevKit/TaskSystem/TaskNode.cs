using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// １つのタスクを扱う制御クラス。
    /// </summary>
    internal class TaskNode : Livet.NotificationObject
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary
        /// <param name="aTaskDepth">タスクの深さ。 <see cref="TaskDepth"/> </param>
        public TaskNode(Task aTask, TaskCategory aCategory, int aTaskDepth)
        {
            Task = aTask;
            Category = aCategory;
            TaskDepth = aTaskDepth;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの分類。
        /// </summary>
        public TaskCategory Category { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの深さ。
        /// </summary>
        /// <remarks>
        /// ルートタスクなら0。子タスクなら1。孫タスクなら2... というように数字が増えていきます。
        /// </remarks>
        public int TaskDepth { get; private set; }

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
        ObservableCollection<TaskNode> _PreparedNodes = new ObservableCollection<TaskNode>(); // 新しいノードはまずここに格納。
        ObservableCollection<TaskNode> _ExecutedNodes = new ObservableCollection<TaskNode>(); // 実行中はこちらに格納。
        ObservableCollection<TaskNode> _FinishedNodes = new ObservableCollection<TaskNode>(); // 何かしらの理由で終了したものはここに格納。

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行する。
        /// </summary>
        public void Execute(TaskExecArg aArg)
        {
            // 状態変更の部分のみロックをかける
            // （ロックをかけ続けると子タスクの状態変化のときにデッドロックになる）
            lock (this)
            {
                if (State != TaskState.Prepared)
                {
                    return;
                }
                State = TaskState.Executed;
            }

            // タスクの実行
            try
            {
                // 本タスク実行
                this.Task.CreateInfo.Action(aArg);

                // 子タスクが残っているなら完了を待つ
                // （子が終わっていないのに自分が完了になってしまうのを防ぐため）
                aArg.WaitAllChildTaskDone();

                // 成功
                State = TaskState.Successed;
            }
            catch (Exception)
            {
                State = TaskState.Failed;
            }                    
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行をキャンセルする。
        /// </summary>
        public void Cancel()
        {
            lock (this)
            {
                switch (State)
                {
                    case TaskState.Prepared:
                        State = TaskState.Canceled;
                        break;
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクを追加する。
        /// </summary>
        public void AddChildTask(TaskNode aTaskNode)
        {
            lock (this)
            {
                aTaskNode.PropertyChanged += ChildTaskNode_PropertyChanged;
                _PreparedNodes.Add(aTaskNode);
            }
        }
        void ChildTaskNode_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            var childNode = (TaskNode)sender;
            if (e.PropertyName == nameof(State))
            {
                // 状態に合わせて移動
                lock (this)
                {
                    if (childNode.State == TaskState.Executed)
                    {
                        _PreparedNodes.Remove(childNode);
                        _ExecutedNodes.Add(childNode);
                    }
                    else
                    {
                        // ここは１つのChildNodeにつき1回しかこないはず。
                        _ExecutedNodes.Remove(childNode);
                        _FinishedNodes.Add(childNode);
                    }
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 全ての子コマンドが終了するのを待つ。
        /// </summary>
        /// <exception cref="ChildTaskNotSuccessedException">いずれかの子タスクの処理が失敗もしくはキャンセルされたら投げられる。</exception>
        public void WaitAllChildTaskDone(AutoResetEvent aEvent, Action aWaitStartedCallback, Action aWaitFinishedCallback)
        {
            // メモ：
            // この関数は１TaskNodeにつき同時に１つしか呼ばれないという前提で実装する

            // 完了待ち関数
            NotifyCollectionChangedEventHandler eventHandler = (aSender, aArgs) =>
            {
                // 追加じゃなければ無視
                if (aArgs.Action != NotifyCollectionChangedAction.Add)
                {
                    return;
                }

                // 全完了しているか確認
                bool isCompleted = false;
                lock (this)
                {
                    if (_PreparedNodes.Count == 0 && _ExecutedNodes.Count == 0)
                    {
                        isCompleted = true;
                    }
                }

                // 全完了しているならスレッドを起こす
                if (isCompleted)
                {
                    aEvent.Set();
                }
            };

            // 既に全てのコマンドが終わっているなら待機をスキップ
            // そうじゃない場合は待ちイベントを開始する
            bool isSkipWait = false;
            lock (this)
            {
                if (_PreparedNodes.Count == 0 && _ExecutedNodes.Count == 0)
                {
                    isSkipWait = true;
                }
                else
                {
                    _FinishedNodes.CollectionChanged += eventHandler;
                }
            }

            // 待機
            if (!isSkipWait)
            {
                aWaitStartedCallback();
                aEvent.WaitOne();
                aWaitFinishedCallback();
                _FinishedNodes.CollectionChanged -= eventHandler;
            }

            // 子タスクで成功していないものがあれば例外を投げる
            bool existsCanceled = _FinishedNodes.Where(child => child.State != TaskState.Canceled).Count() != 0;
            bool existsFailed = _FinishedNodes.Where(child => child.State != TaskState.Failed).Count() != 0;
            if (existsCanceled || existsFailed)
            {
                throw new ChildTaskNotSuccessedException(existsCanceled, existsFailed);
            }
        }
    }
}
