using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdelDevKit.TaskSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            }
            Assert.IsTrue(flag);
        }

        [TestMethod()]
        public void DisposeTest()
        {
            using (var mgr = new TaskManager())
            {
            }
        }
    }
}