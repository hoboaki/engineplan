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
        /// ロードされたビルダーアドオン群。
        /// </summary>
        public IBuilderAddon[] BuilderAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// アドオンロード後に呼ばれる関数。
        /// </summary>
        internal void OnAddonLoaded(PluginSystem.IAddon[] aAddons, Setting.SettingManager aSettingManager)
        {
            // ビルダーアドオンを収集
            BuilderAddons = aAddons.Where(x => x is IBuilderAddon).Select(x => (IBuilderAddon)x).ToArray();

            // BuildTarget を生成
            // ...
        }
    }
}
