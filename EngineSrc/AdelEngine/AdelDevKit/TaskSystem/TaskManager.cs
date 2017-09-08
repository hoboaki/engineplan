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
    public class TaskManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskManager()
        {
            _ParallelCount = 8; // 暫定数
            _SleepThreadCount = 0;
            for (int i = 0; i < _ParallelCount; ++i)
            {
                CreateActiveTaskThread();
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの追加。
        /// </summary>
        public void Add(Task aTask)
        {
            // TaskNode化して追加
            int taskDepth = 0;
            AddTaskNode(new TaskNode(aTask, taskDepth));
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
        ObservableCollection<TaskNode> _PreparedTaskNodes = new ObservableCollection<TaskNode>();
        ObservableCollection<TaskNode> _ExecutedTaskNodes = new ObservableCollection<TaskNode>();
        List<TaskThread> _ActiveThreads = new List<TaskThread>();
        List<AutoResetEvent> _ActiveWaitEvents = new List<AutoResetEvent>();
        List<SuspendInfo> _SuspendInfos = new List<SuspendInfo>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// 新しいタスクスレッドを追加。
        /// </summary>
        void CreateActiveTaskThread()
        {
            _ActiveThreads.Add(new TaskThread(PullNextTaskFunc, PushChildTaskFunc, ChildTaskWaitStartedCallback, ChildTaskWaitFinishedCallback));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクノードの追加。
        /// </summary>
        void AddTaskNode(TaskNode aTaskNode)
        {
            lock (this)
            {
                _PreparedTaskNodes.Add(aTaskNode);

                // イベント待ちしているスレッドがあれば起こす
                AutoResetEvent[] wakeEvents;
                lock (_ActiveWaitEvents)
                {
                    // 全スレッド起こす暫定実装
                    // 将来的にはCPUの状況やアプリの実行状態を見て同時実行数を動的に制御する
                    wakeEvents = _ActiveWaitEvents.ToArray();
                    _ActiveWaitEvents.Clear();
                    foreach (var wakeEvent in wakeEvents)
                    {
                        wakeEvent.Set();
                    }
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
                        if (0 < _PreparedTaskNodes.Count)
                        {
                            result = _PreparedTaskNodes[0];
                            _PreparedTaskNodes.RemoveAt(0);
                            _ExecutedTaskNodes.Add(result);
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
