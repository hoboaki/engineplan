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
    class AddonInfo<TAddonType> where TAddonType:IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal AddonInfo(TAddonType aAddon, PluginInfo aPluginInfo)
        {
            Addon = aAddon;
            PluginInfo = aPluginInfo;
        }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// アドオン実体。
        /// </summary>
        internal TAddonType Addon { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 所属するプラグイン。
        /// </summary>
        internal PluginInfo PluginInfo { get; private set; }
    }
}
