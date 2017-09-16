using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// アドオン情報。
    /// </summary>
    class AddonInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal AddonInfo(IAddon aAddon, PluginInfo aPluginInfo)
        {
            Addon = aAddon;
            PluginInfo = aPluginInfo;
        }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// アドオン実体。
        /// </summary>
        internal IAddon Addon { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 所属するプラグイン。
        /// </summary>
        internal PluginInfo PluginInfo { get; private set; }
    }
}
