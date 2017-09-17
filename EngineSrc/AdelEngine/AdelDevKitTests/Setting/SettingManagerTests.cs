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
            var log = new CommandLog.Logger();
            settingManager.Load(log, new DirectoryInfo(testProjectDir));
            Assert.IsTrue(log.Text.Length == 0);
            Assert.IsTrue(settingManager.PlatformSettings.Length == 1);
            Assert.AreEqual("MyProject", settingManager.ProjectSetting.Name);
            Assert.AreEqual("Win-Gl330", settingManager.PlatformSettings[0].Name);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト設定がないエラーを補則するテスト。
        /// </summary>
        [TestMethod()]
        public void NotFoundProjectSettingTest()
        {
            string testProjectDir = TestsProjectDirPath + @"NotFoundProjectSettingProject\Setting";
            var settingManager = new SettingManager();
            var log = new CommandLog.Logger();
            try
            {
                settingManager.Load(log, new DirectoryInfo(testProjectDir));
                Assert.Fail();
            } catch(CommandLog.MessagedException)
            {
            }
            Assert.IsTrue(settingManager.ProjectSetting == null);
            Assert.IsTrue(log.Text.Contains("プロジェクト設定"));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 無効なプラットフォーム設定エラーを捕捉するテスト。
        /// </summary>
        [TestMethod()]
        public void InvalidPlatformSettingTest()
        {
            string testProjectDir = TestsProjectDirPath + @"InvalidPlatformSettingProject\Setting";
            var settingManager = new SettingManager();
            var log = new CommandLog.Logger();
            try
            {
                settingManager.Load(log, new DirectoryInfo(testProjectDir));
                Assert.Fail();
            }
            catch (CommandLog.MessagedException)
            {
            }
            Assert.IsTrue(log.Text.Contains("設定ファイル"));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 同名プラットフォーム設定エラーを捕捉するテスト。
        /// </summary>
        [TestMethod()]
        public void SamePlatformNameErrorTest()
        {
            string testProjectDir = TestsProjectDirPath + @"SamePlatformNameErrorProject\Setting";
            var settingManager = new SettingManager();
            var log = new CommandLog.Logger();
            try
            {
                settingManager.Load(log, new DirectoryInfo(testProjectDir));
                Assert.Fail();
            }
            catch (CommandLog.MessagedException)
            {
            }
            Assert.IsTrue(0 < log.Text.Length);
            Assert.IsTrue(log.Text.Contains("複数定義"));
        }

    }
}