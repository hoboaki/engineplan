using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 開発キットのあらゆるオブジェクトへのアクセスを提供するクラス。
    /// </summary>
    public class DevKit : IDisposable
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal DevKit(CommandLog.Logger aLog, DirectoryInfo aProjectDir)
        {
            // 引数チェック
            if (!aProjectDir.Exists)
            {
                aLog.Error.WriteLine("指定されたプロジェクトフォルダ'{0}'は存在しません。", aProjectDir.FullName);
                throw new CommandLog.MessagedException();
            }
            

            // オブジェクト生成
            BuildManager = new BuildSystem.BuildManager();
            ConfigManager = new Config.ConfigManager();
            CoreLibManager = new CoreLib.CoreLibManager();
            EnvInfo = new EnvInfo()
            {
                ProjectRootDir = aProjectDir,
            };
            PluginManager = new PluginSystem.PluginManager();
            SettingManager = new Setting.SettingManager();
            TaskManager = new TaskSystem.TaskManager();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// デストラクタ。
        /// </summary>
        ~DevKit()
        {
            Dispose();
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
        /// CoreLibマネージャ。
        /// </summary>
        public CoreLib.CoreLibManager CoreLibManager { get; private set; }

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

        //------------------------------------------------------------------------------
        /// <summary>
        /// なるべく速く全てのスレッドを終了させる。
        /// </summary>
        /// <remarks>
        /// ここに到達するのはアプリケーションの終了時のみとなり、早さが求められる。
        /// そのため登録済みのタスクを全て処理せず、できる限りタスクをキャンセルする。
        /// </remarks>
        public void Dispose()
        {
            if (!_IsDisposing)
            {
                // フラグオン
                _IsDisposing = true;

                // 各オブジェクトをディスポーズ
                TaskManager?.Dispose();
            }
        }
        bool _IsDisposing = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード処理を行う。
        /// </summary>
        public void Load(CommandLog.Logger aLog)
        {
            // プラグイン＆アドオンをロード
            {
                var dirList = new List<DirectoryInfo>();
                if (EnvInfo.ProjectPluginDir.Exists)
                {
                    dirList.Add(EnvInfo.ProjectPluginDir);
                }
                PluginManager.Load(aLog, dirList.ToArray());
            }

            // 以下、依存関係順にセットアップ
            SettingManager.Load(aLog, EnvInfo.ProjectSettingDir);
            CoreLibManager.Load(aLog, PluginManager);
            BuildManager.Load(aLog, PluginManager, SettingManager, CoreLibManager);
        }

    }
}
