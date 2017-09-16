using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CoreLib
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// CoreLib を扱うクラス。
    /// </summary>
    public class CoreLibManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal CoreLibManager()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreOs 群。
        /// </summary>
        internal ICoreOsAddon[] CoreOsAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreGfx 群。
        /// </summary>
        internal ICoreGfxAddon[] CoreGfxAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreSnd 群。
        /// </summary>
        internal ICoreSndAddon[] CoreSndAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 各 CoreLib を生成する。
        /// </summary>
        internal void Load(
            CommandLog.Logger aLog,
            PluginSystem.PluginManager aPluginManager
            )
        {
            // チェック
            System.Diagnostics.Debug.Assert(aPluginManager.IsLoaded);

            // アドオン収集
            CoreOsAddons = aPluginManager.Addons.Where(x => x is ICoreOsAddon).Select(x => (ICoreOsAddon)x).ToArray();
            CoreGfxAddons = aPluginManager.Addons.Where(x => x is ICoreGfxAddon).Select(x => (ICoreGfxAddon)x).ToArray();
            CoreSndAddons = aPluginManager.Addons.Where(x => x is ICoreSndAddon).Select(x => (ICoreSndAddon)x).ToArray();

            // 重複チェック
        }
    }
}
