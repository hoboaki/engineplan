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
                mgr.Add(task, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
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
                mgr.Add(parentTask, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
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
                mgr.Add(parentTask, TaskCategory.BatchProcess);
                mgr.WaitAllTaskDone();
            }
            Assert.IsTrue(flag);
        }
    }
}