using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdelDevKit.TaskSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace AdelDevKit.TaskSystem.Tests
{
    [TestClass()]
    public class TaskManagerTests
    {
        [TestMethod()]
        public void TaskManagerTest()
        {
        }
        
        [TestMethod()]
        public void DisposeTest()
        {
            using (var mgr = new TaskManager())
            {
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクを1個だけ実行するテスト。
        /// </summary>
        [TestMethod()]
        public void SimpleTaskTest()
        {
            bool flag = false;
            using (var mgr = new TaskManager())
            {
                var task = new Task(new TaskCreateInfo(
                    (arg) =>
                    {
                        flag = true;
                    }
                    ));
                var node = mgr.Add(task, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Successed, node.State);
            }
            Assert.IsTrue(flag);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクの作成と同期のテスト。
        /// </summary>
        [TestMethod()]
        public void ChildTaskTest()
        {
            bool flagA = false;
            bool flagB = false;
            bool flagC = false;
            using (var mgr = new TaskManager())
            {
                var parentTask = new Task(new TaskCreateInfo(
                    (a0) =>
                    {
                        Assert.IsFalse(flagA);
                        Assert.IsFalse(flagB);
                        Assert.IsFalse(flagC);
                        flagA = true;

                        // 子タスクを追加
                        var childTask = new Task(new TaskCreateInfo(
                            (a1) =>
                            {
                                Assert.IsTrue(flagA);
                                Assert.IsFalse(flagB);
                                Assert.IsFalse(flagC);
                                flagB = true;
                            }
                            ));
                        a0.ExecChildTaskAsync(childTask);
                        a0.WaitAllChildTaskDone();

                        Assert.IsTrue(flagA);
                        Assert.IsTrue(flagB);
                        Assert.IsFalse(flagC);
                        flagC = true;

                    }
                    ));
                var node = mgr.Add(parentTask, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Successed, node.State);
            }
            Assert.IsTrue(flagA);
            Assert.IsTrue(flagB);
            Assert.IsTrue(flagC);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクの並列実行テスト。
        /// </summary>
        [TestMethod()]
        public void ChildParallelTaskTest()
        {
            int counter = 0;
            bool flag = false;
            int parallelCount = 100;
            using (var mgr = new TaskManager())
            {
                var parentTask = new Task(new TaskCreateInfo(
                    (a0) =>
                    {
                        // 子タスクを追加
                        var childTask = new Task(new TaskCreateInfo(
                            (a1) =>
                            {
                                Interlocked.Add(ref counter, 1);
                            }
                            ));

                        // 指定回数追加＆待ち
                        for (int i = 0; i < parallelCount; ++i)
                        {
                            a0.ExecChildTaskAsync(childTask);
                        }
                        a0.WaitAllChildTaskDone();

                        // チェック
                        Assert.AreEqual(counter, parallelCount);
                        flag = true;

                    }
                    ));
                var node = mgr.Add(parentTask, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Successed, node.State);
            }
            Assert.IsTrue(flag);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの成功と失敗のテスト。
        /// </summary>
        [TestMethod()]
        public void SuccessAndFailureTest()
        {
            using (var mgr = new TaskManager())
            {
                var taskSuccess = new Task(new TaskCreateInfo(
                    (arg) => {}
                    ));
                var taskFailure = new Task(new TaskCreateInfo(
                    (arg) => { throw new Exception(); }
                    ));
                var nodeSuccess = mgr.Add(taskSuccess, TaskCategory.BatchProcess);
                var nodeFailure = mgr.Add(taskFailure, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Successed, nodeSuccess.State);
                Assert.AreEqual(TaskState.Failed, nodeFailure.State);
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 子タスクの失敗のテスト。
        /// </summary>
        [TestMethod()]
        public void FailureChildTest()
        {
            using (var mgr = new TaskManager())
            {
                var parentTask = new Task(new TaskCreateInfo(
                    (a0) =>
                    {
                        // 子タスクを追加
                        var childTask = new Task(new TaskCreateInfo(
                            (a1) =>
                            {
                                throw new Exception();
                            }
                            ));
                        a0.ExecChildTaskAsync(childTask);
                        a0.WaitAllChildTaskDone();

                        Assert.Fail(); // 到達しない場所
                    }
                    ));
                var node = mgr.Add(parentTask, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Failed, node.State);
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクプライオリティのテスト。
        /// </summary>
        [TestMethod()]
        public void PriorityTaskTest()
        {
            using (var mgr = new TaskManager())
            {
                var priorityLo = TaskCategory.AssetBuild;
                var priorityHi = TaskCategory.BatchProcess;
                Assert.IsTrue((int)(priorityHi) < (int)(priorityLo));

                int childTaskCount = 100;
                int counter = 0;
                bool isHiTaskFinished = false;
                var taskHi = new Task(new TaskCreateInfo(
                    (a) =>
                    {
                        Assert.IsTrue(counter < (childTaskCount / 2)); // 速やかに実行されているはず。
                        isHiTaskFinished = true;
                    }
                    ));
                var taskLo = new Task(new TaskCreateInfo(
                    (a0) =>
                    {
                        // 子タスクを追加
                        var childTask = new Task(new TaskCreateInfo(
                            (a1) =>
                            {
                                // 少し長めの処理を想定してスリープ。
                                Thread.Sleep(100); // 100msec
                                Interlocked.Add(ref counter, 1);
                            }
                            ));
                        for (int i = 0; i < childTaskCount; ++i)
                        {
                            a0.ExecChildTaskAsync(childTask);
                        }
                        a0.WaitAllChildTaskDone();

                        // 100個処理するよりも前に優先度の高いタスクは終わっているはず
                        Assert.IsTrue(isHiTaskFinished);
                    }
                    ));
                var nodeLo = mgr.Add(taskLo, priorityLo);
                Thread.Sleep(100); // 100msec
                var nodeHi = mgr.Add(taskHi, priorityHi);
                mgr.WaitAllTaskDone();
                Assert.AreEqual(TaskState.Successed, nodeLo.State);
                Assert.AreEqual(TaskState.Successed, nodeHi.State);
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// コマンドログのテスト。
        /// </summary>
        [TestMethod()]
        public void LogTest()
        {
            using (var mgr = new TaskManager())
            {
                string TextDebug = "This is Debug.";
                string TextInfo = "This is Info.";
                string TextWarn = "This is Warn.";
                string TextError = "This is Error.";
                var task = new Task(new TaskCreateInfo(
                    (arg) =>
                    {
                        var log = arg.Log;
                        log.Debug.WriteLine(TextDebug);
                        log.Info.WriteLine(TextInfo);
                        log.Warn.WriteLine(TextWarn);
                        log.Error.WriteLine(TextError);
                    }
                    ));
                var node = mgr.Add(task, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();

                var newLine = node.Log.Debug.NewLine;
                Assert.AreEqual(node.Log.GetText(CommandLog.LogKind.Debug), TextDebug + newLine);
                Assert.AreEqual(node.Log.GetText(CommandLog.LogKind.Info), TextInfo + newLine);
                Assert.AreEqual(node.Log.GetText(CommandLog.LogKind.Warn), TextWarn + newLine);
                Assert.AreEqual(node.Log.GetText(CommandLog.LogKind.Error), TextError + newLine);
            }
        }

    }
}