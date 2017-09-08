using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    /// <summary>
    /// タスクを処理するスレッド。
    /// </summary>
    class TaskThread
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// 次のタスクを取得する関数。
        /// </summary>
        public delegate TaskNode PullNextTaskFunc(TaskThread aSenderThread, AutoResetEvent aWakeEvent);

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskThread(PullNextTaskFunc aPullNextTaskFunc)
        {
            _PullNextTaskFunc = aPullNextTaskFunc;
            _Thread = new Thread(ThreadMain);
        }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// スレッドのメイン関数。
        /// </summary>
        void ThreadMain()
        {
            // 次々とタスクを実行
            while (true)
            {
                // 次のタスクを取得
                TaskNode next = _PullNextTaskFunc(this, _WakeEvent);
                if (next == null)
                {
                    // null が返ってきたら終了
                    break;
                }

                // 実行
                //next.Execute();
            }
        }

        //------------------------------------------------------------------------------
        PullNextTaskFunc _PullNextTaskFunc;
        Thread _Thread;
        AutoResetEvent _WakeEvent = new AutoResetEvent(false); // 起動用イベント。最初は寝ている状態にしたいのでfalseで初期化。
    }
}
