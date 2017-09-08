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
        /// 新しい子タスクを追加する関数。
        /// </summary>
        public delegate void PushChildTaskFunc(TaskNode aChildTask);

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスク待ち開始時のコールバック関数。
        /// </summary>
        public delegate void ChildTaskWaitStartedCallback();

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスク待ち終了時のコールバック関数。
        /// </summary>
        public delegate void ChildTaskWaitFinishedCallback();

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskThread(
            PullNextTaskFunc aPullNextTaskFunc, 
            PushChildTaskFunc aPushChildTaskFunc, 
            ChildTaskWaitStartedCallback aWaitStartedCallback, 
            ChildTaskWaitFinishedCallback aWaitFinishedCallback
            )
        {
            _PullNextTaskFunc = aPullNextTaskFunc;
            _PushChildTaskFunc = aPushChildTaskFunc;
            _WaitStartedCallback = aWaitStartedCallback;
            _WaitFinishedCallback = aWaitFinishedCallback;
            _Thread = new Thread(ThreadMain);
        }

        //------------------------------------------------------------------------------
        PullNextTaskFunc _PullNextTaskFunc;
        PushChildTaskFunc _PushChildTaskFunc;
        ChildTaskWaitStartedCallback _WaitStartedCallback;
        ChildTaskWaitFinishedCallback _WaitFinishedCallback;
        Thread _Thread;
        AutoResetEvent _WakeEvent = new AutoResetEvent(false); // 起動用イベント。最初は寝ている状態にしたいのでfalseで初期化。
        
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

                // 実行引数を作成
                TaskExecArg.ExecChildTaskFunc execChildTaskFunc = (aNewTask) =>
                {
                    // タスクノードを作成
                    var childNode = new TaskNode(aNewTask, next.TaskDepth + 1);

                    // 親ノードに登録
                    next.AddChildTask(childNode);

                    // タスクマネージャに登録
                    _PushChildTaskFunc(childNode);
                };
                TaskExecArg.WaitAllChildTaskDoneFunc waitAllChildTaskDoneFunc = () =>
                {
                    Action waitStartedCallback = () => { _WaitStartedCallback(); };
                    Action waitFinishedCallback = () => { _WaitFinishedCallback(); };
                    next.WaitAllChildTaskDone(
                        _WakeEvent, 
                        waitStartedCallback, 
                        waitFinishedCallback
                        );
                };

                // 実行
                next.Execute(new TaskExecArg(
                    new Logger(), // 仮コード
                    execChildTaskFunc,
                    waitAllChildTaskDoneFunc
                    ));
            }
        }
    }
}
