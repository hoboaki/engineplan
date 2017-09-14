using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdelDevKit.Setting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace AdelDevKit.Setting.Tests
{
    [TestClass()]
    public class SettingManagerTests
    {
        [TestMethod()]
        public void LoadTest()
        {
            string testProjectDir = Directory.GetCurrentDirectory() + @"\..\..\..\..\TestProject\SimpleProject\Setting";
            var settingManager = new SettingManager();
            settingManager.Load(new DirectoryInfo(testProjectDir));
            Assert.IsTrue(settingManager.Logger.Text.Length == 0);
            Assert.IsTrue(settingManager.PlatformSettings.Length == 1);
            Assert.AreEqual("MyProject", settingManager.ProjectSetting.Name);
            Assert.AreEqual("win - dx11", settingManager.PlatformSettings[0].Name);
        }
    }
}