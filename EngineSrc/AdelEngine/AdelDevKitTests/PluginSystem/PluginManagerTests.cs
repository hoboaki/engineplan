using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdelDevKit.PluginSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace AdelDevKit.PluginSystem.Tests
{
    [TestClass()]
    public class PluginManagerTests
    {
        [TestMethod()]
        public void LoadTest()
        {
            string pluginsDirPath = System.IO.Directory.GetCurrentDirectory() + @"\..\..\..\AdelDevKitTestsPlugin\bin";
            var pluginsDirs = new List<DirectoryInfo>();
            pluginsDirs.Add(new DirectoryInfo(pluginsDirPath));

            var pluginManager = new PluginSystem.PluginManager();
            var log = new CommandLog.Logger();
            pluginManager.Load(log, pluginsDirs.ToArray());

            Assert.IsTrue(0 < pluginManager.PluginUnits.Length);
            Assert.IsTrue(0 < pluginManager.Addons.Length);
        }
    }
}