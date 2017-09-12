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
    public class PluginManager
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
        /// <param name="aPluginRootDirectories">*.aeplugin フォルダが置かれているルートフォルダ群。</param>
        /// <exception cref="FileNotFoundException">*.aeplugin 以下に命名規則通りの DLL ファイルがない場合に投げられます。</exception>
        internal void Load(DirectoryInfo[] aPluginRootDirectories)
        {
            foreach (var pluginRootDir in aPluginRootDirectories)
            {
                foreach (var pluginDir in pluginRootDir.EnumerateDirectories("*.aeplugin"))
                {
                    // DLLファイルをロード
                    var baseName = pluginDir.Name.Substring(0, pluginDir.Name.Length - pluginDir.Extension.Length);
                    var dllPath = pluginDir.FullName + @"\DevKitDll";
                    if (!Directory.Exists(dllPath))
                    {
                        throw new FileNotFoundException(String.Format("プラグインフォルダ'{0}' に DevKitDll フォルダがありません。", pluginDir.FullName) , dllPath);
                    }
                    _PluginEntries.Add(new PluginEntry(new DirectoryInfo(dllPath)));
                }
            }
        }

        List<PluginEntry> _PluginEntries = new List<PluginEntry>();
    }
}
