using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 開発キットのあらゆるオブジェクトへのアクセスを提供するクラス。
    /// </summary>
    public class DevKit
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal DevKit(CommandLog.Logger aLog)
        {
            // オブジェクト生成
            BuildManager = new BuildSystem.BuildManager();
            ConfigManager = new Config.ConfigManager();
            EnvInfo = new EnvInfo();
            PluginManager = new PluginSystem.PluginManager();
            SettingManager = new Setting.SettingManager(aLog);
            TaskManager = new TaskSystem.TaskManager();

            // プラグイン＆アドオンをロード
            PluginManager.Load(null);

            // 以下、依存関係順にセットアップ
            SettingManager.Load(EnvInfo.SettingDir);
            BuildManager.OnAddonLoaded(PluginManager.Addons, SettingManager);
        }

        #region オブジェクト群（ABC順）
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドマネージャ。
        /// </summary>
        public BuildSystem.BuildManager BuildManager { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 動的設定情報マネージャ。
        /// </summary>
        public Config.ConfigManager ConfigManager { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 環境情報。
        /// </summary>
        public EnvInfo EnvInfo { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグインマネージャ。
        /// </summary>
        public PluginSystem.PluginManager PluginManager { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 静的設定情報マネージャ。
        /// </summary>
        public Setting.SettingManager SettingManager { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクマネージャ。
        /// </summary>
        public TaskSystem.TaskManager TaskManager { get; private set; }

        #endregion
    }
}
