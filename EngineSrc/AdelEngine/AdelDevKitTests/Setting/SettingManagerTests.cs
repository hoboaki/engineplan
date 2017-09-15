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
        string TestsProjectDirPath { get { return Directory.GetCurrentDirectory() + @"\..\..\..\..\TestsProject\SettingTests\"; } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// シンプルな設定をロードするテスト。
        /// </summary>
        [TestMethod()]
        public void LoadTest()
        {
            string testProjectDir = TestsProjectDirPath + @"SimpleProject\Setting";
            var settingManager = new SettingManager();
            settingManager.Load(new DirectoryInfo(testProjectDir));
            Assert.IsTrue(settingManager.Logger.Text.Length == 0);
            Assert.IsTrue(settingManager.PlatformSettings.Length == 1);
            Assert.AreEqual("MyProject", settingManager.ProjectSetting.Name);
            Assert.AreEqual("win-gl330", settingManager.PlatformSettings[0].Name);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト設定がないエラーを補則するテスト。
        /// </summary>
        [TestMethod()]
        public void NotFoundProjectSettingTest()
        {
            string testProjectDir = TestsProjectDirPath + @"InvalidPlatformSettingProject\Setting";
            var settingManager = new SettingManager();
            settingManager.Load(new DirectoryInfo(testProjectDir));
            Assert.IsTrue(settingManager.ProjectSetting != null);
            Assert.IsTrue(0 < settingManager.Logger.Text.Length);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 無効なプラットフォーム設定エラーを捕捉するテスト。
        /// </summary>
        [TestMethod()]
        public void InvalidPlatformSettingTest()
        {
            string testProjectDir = TestsProjectDirPath + @"NotFoundProjectSettingProject\Setting";
            var settingManager = new SettingManager();
            settingManager.Load(new DirectoryInfo(testProjectDir));
            Assert.IsTrue(0 < settingManager.Logger.Text.Length);
            Assert.IsTrue(settingManager.ProjectSetting == null);
        }

    }
}