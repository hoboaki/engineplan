using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドシステムの管理クラス。
    /// </summary>
    public class BuildManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal BuildManager()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダー群。
        /// </summary>
        public Builder[] Builders{ get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット群。
        /// </summary>
        public BuildTarget[] BuildTargets { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーを生成する。
        /// </summary>
        internal void Load(
            CommandLog.Logger aLog,
            PluginSystem.PluginManager aPluginManager, 
            Setting.SettingManager aSettingManager, 
            CoreLib.CoreLibManager aCoreLibManager
            )
        {
            // チェック
            System.Diagnostics.Debug.Assert(aPluginManager.IsLoaded);
            System.Diagnostics.Debug.Assert(aSettingManager.IsLoaded);
            System.Diagnostics.Debug.Assert(aCoreLibManager.IsLoaded);

            // ビルダーアドオンを収集
            var addons = aPluginManager.Addons.Where(x => x is IBuilderAddon).Select(x => (IBuilderAddon)x).ToArray();

            // 重複チェック

            // ビルダーを生成
            var builders = new List<Builder>();
            foreach (var addon in addons)
            {
                builders.Add(new Builder(addon));
            }
            Builders = builders.ToArray();

            // ビルドターゲットを作成
            var buildTargets = new List<BuildTarget>();
            foreach (var platfomSetting in aSettingManager.PlatformSettings)
            {
                foreach (var buildTargetSetting in platfomSetting.BuildTargetSettings)
                {
                    buildTargets.Add(new BuildSystem.BuildTarget(aLog, platfomSetting, buildTargetSetting, Builders));
                }
            }
            BuildTargets = buildTargets.ToArray();
        }
    }
}
