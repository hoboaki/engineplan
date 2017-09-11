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
            pluginManager.Load(pluginsDirs.ToArray());

            foreach(var pluginsDir in pluginsDirs)
            {
                foreach (var eachPluginDir in pluginsDir.EnumerateDirectories("*.aeplugin"))
                {
                    var baseName = eachPluginDir.Name.Substring(0, eachPluginDir.Name.Length - eachPluginDir.Extension.Length);
                    var dllPath = eachPluginDir.FullName + @"\" + baseName + ".dll";
                    Assert.IsTrue(File.Exists(dllPath));
                }

            }
        }
    }
}