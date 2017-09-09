using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクを実行管理するクラス。
    /// </summary>
    /// <remarks>
    /// 全ての <see cref="Task"/> の実行を管理するクラスです。
    /// 追加されたタスクは優先順位を考慮しつつできる限り並列に実行します。
    /// </remarks>
    public class TaskManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskManager()
        {
            // 初期設定
            _ParallelCount = 8; // 暫定数
            _SleepThreadCount = 0;

            // タスクノード管理クラス作成
            var nodeManager = new List<TaskSystem.TaskNodeManager>();
            nodeManager.Add(new TaskSystem.TaskNodeManager(TaskCategory.VcsProcess));
            nodeManager.Add(new TaskSystem.TaskNodeManager(TaskCategory.BatchProcess));
            nodeManager.Add(new TaskSystem.TaskNodeManager(TaskCategory.AssetBuild));
            nodeManager.Add(new TaskSystem.TaskNodeManager(TaskCategory.ExecutableFileBuild));
            nodeManager.ForEach((x) => _NodeManagers.Add(x.Category, x));

            // スレッド作成
            for (int i = 0; i < _ParallelCount; ++i)
            {
                CreateActiveTaskThread();
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの追加。
        /// </summary>
        internal void Add(Task aTask, TaskCategory aCategory)
        {
            // TaskNode化して追加
            int taskDepth = 0;
            AddTaskNode(new TaskNode(aTask, aCategory, taskDepth));
        }

        //------------------------------------------------------------------------------
        class SuspendInfo
        {
            public TaskThread Thread;
            public AutoResetEvent WakeEvent;
        }

        //------------------------------------------------------------------------------
        int _ParallelCount; // 並列実行数。
        int _SleepThreadCount; // _ActiveTaskThreads の中でスリープ中のスレッド数。
        Dictionary<TaskCategory, TaskNodeManager> _NodeManagers = new Dictionary<TaskCategory, TaskNodeManager>();
        List<TaskThread> _ActiveThreads = new List<TaskThread>();
        List<AutoResetEvent> _ActiveWaitEvents = new List<AutoResetEvent>();
        List<SuspendInfo> _SuspendInfos = new List<SuspendInfo>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// 新しいタスクスレッドを追加。
        /// </summary>
        void CreateActiveTaskThread()
        {
            var thread = new TaskThread(PullNextTaskFunc, PushChildTaskFunc, ChildTaskWaitStartedCallback, ChildTaskWaitFinishedCallback);
            _ActiveThreads.Add(thread);
            thread.Start();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクノードの追加。
        /// </summary>
        void AddTaskNode(TaskNode aTaskNode)
        {
            lock (this)
            {
                // ノードを追加
                _NodeManagers[aTaskNode.Category].Add(aTaskNode);
                
                // イベント待ちしているスレッドがあれば起こす
                AutoResetEvent[] wakeEvents = _ActiveWaitEvents.ToArray();
                _ActiveWaitEvents.Clear();
                foreach (var wakeEvent in wakeEvents)
                {
                    wakeEvent.Set();
                }
            }

        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 次のタスクを取得する関数。各スレッドから呼ばれる関数。
        /// </summary>
        TaskNode PullNextTaskFunc(TaskThread aSenderThread, AutoResetEvent aWakeEvent)
        {
            TaskNode result = null;
            while (result == null)
            {
                lock (this)
                {
                    // 同時実行上限を超えている場合
                    if (_ParallelCount + _SleepThreadCount < _ActiveThreads.Count())
                    {
                        // 一時停止状態に移行する
                        _ActiveThreads.Remove(aSenderThread);
                        _SuspendInfos.Add(new SuspendInfo() { Thread = aSenderThread, WakeEvent = aWakeEvent });
                    }
                    else
                    {
                        // 既にあるタスクを取得して返す
                        foreach (var nodeManager in _NodeManagers)
                        {
                            result = nodeManager.Value.PullNextTask();
                            if (result != null)
                            {
                                break;
                            }
                        }

                        // タスクが取得できたら while ループから抜けてタスクの実行に移る
                        if (result != null)
                        {
                            break;
                        }

                        // なければ待ちイベントに追加
                        _ActiveWaitEvents.Add(aWakeEvent);
                    }
                }

                // 追加もしくは一時停止解除まで待つ
                aWakeEvent.WaitOne();
            }
            return result;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 新規子タスクを追加する関数。各スレッドから呼ばれる関数。
        /// </summary>
        void PushChildTaskFunc(TaskNode aNewNode)
        {
            AddTaskNode(aNewNode);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスク待ちが開始されたときに呼ばれる関数。各スレッドから呼ばれる関数。
        /// </summary>
        void ChildTaskWaitStartedCallback()
        {
            lock(this)
            {
                // 非スリープ中なアクティブスレッドの数が _ParallelCount と同じになるように調整する
                ++_SleepThreadCount;
                while (_ActiveThreads.Count() < _ParallelCount + _SleepThreadCount)
                {
                    if (0 < _SuspendInfos.Count())
                    {
                        // 一時停止中のスレッドがあるならそちらをActiveに変更
                        var wakeupInfo = _SuspendInfos[0];
                        _SuspendInfos.RemoveAt(0);
                        _ActiveThreads.Add(wakeupInfo.Thread);
                        _ActiveWaitEvents.Add(wakeupInfo.WakeEvent);
                    }
                    else
                    {
                        // 新規スレッドを作る
                        CreateActiveTaskThread();
                    }
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスク待ちが終了されたときに呼ばれる関数。各スレッドから呼ばれる関数。
        /// </summary>
        void ChildTaskWaitFinishedCallback()
        {
            lock (this)
            {
                // 数だけ減らし、実際にActiveスレッドの数のコントロールは別の箇所で行う
                --_SleepThreadCount;
            }
        }
    }
}
