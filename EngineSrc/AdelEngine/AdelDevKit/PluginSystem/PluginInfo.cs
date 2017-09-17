using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// プラグイン情報。
    /// </summary>
    class PluginInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal PluginInfo(IPlugin aPlugin, FileInfo aFileInfo)
        {
            Plugin = aPlugin;
            FileInfo = aFileInfo;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグイン本体。
        /// </summary>
        internal IPlugin Plugin { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 組み込まれていたファイル。
        /// </summary>
        internal FileInfo FileInfo { get; private set; }
    }
}
