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
        /// アドオンロード後に呼ばれる関数。
        /// </summary>
        internal void OnAddonLoaded(PluginSystem.IAddon[] aAddons)
        {

        }
    }
}
