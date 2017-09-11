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
    /// プラグイン（<see cref="PluginInterface.IPlugin"/>）とプラグインが提供するアドオン（<see cref="IAddon"/>）を管理するクラス。
    /// </summary>
    internal class PluginManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal PluginManager()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグインを読み込みアドオンを作成する。
        /// </summary>
        /// <param name="aPluginDirectories">*.aeplugin フォルダが置かれているフォルダ群。</param>
        internal void Load(DirectoryInfo[] aPluginDirectories)
        {
        }
    }
}
