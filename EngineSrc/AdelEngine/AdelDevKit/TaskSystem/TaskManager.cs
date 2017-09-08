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
            int parallelCount = 8; // 暫定数
            for (int i = 0; i < parallelCount; ++i)
            {
                _TaskThreads.Add(new TaskThread(PullNextTaskFunc));
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの追加。
        /// </summary>
        public void Add(Task aTask)
        {
            lock (this)
            {
                // TaskNode化していく
                int taskDepth = 0;
                _PreparedTaskNodes.Add(new TaskNode(aTask, taskDepth));

                // イベント待ちしているスレッドがあれば起こす
                AutoResetEvent[] wakeEvents;
                lock (_WaitEvents)
                {
                    // 全スレッド起こす暫定実装
                    // 将来的にはCPUの状況やアプリの実行状態を見て同時実行数を動的に制御する
                    wakeEvents = _WaitEvents.ToArray();
                    _WaitEvents.Clear();
                }
                foreach (var wakeEvent in wakeEvents)
                {
                    wakeEvent.Set();
                }
            }
        }
        
        //------------------------------------------------------------------------------
        ObservableCollection<TaskNode> _PreparedTaskNodes = new ObservableCollection<TaskNode>();
        ObservableCollection<TaskNode> _ExecutedTaskNodes = new ObservableCollection<TaskNode>();
        List<TaskThread> _TaskThreads = new List<TaskThread>();
        List<AutoResetEvent> _WaitEvents = new List<AutoResetEvent>();

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
                    // 既にあるタスクを取得して返す
                    if (0 < _PreparedTaskNodes.Count)
                    {
                        result = _PreparedTaskNodes[0];
                        _PreparedTaskNodes.RemoveAt(0);
                        _ExecutedTaskNodes.Add(result);
                        break;
                    }

                    // なければ待ちイベントに追加
                    _WaitEvents.Add(aWakeEvent);
                }

                // 追加されるまで待つ
                aWakeEvent.WaitOne();
            }
            return result;
        }
    }
}
