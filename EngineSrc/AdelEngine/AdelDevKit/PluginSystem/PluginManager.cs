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
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードしたプラグイン群。
        /// </summary>
        internal PluginUnit[] PluginUnits { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードした全アドオン。
        /// </summary>
        internal AddonInfo<IAddon>[] Addons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグインを読み込みアドオンを作成する。
        /// </summary>
        /// <param name="aPluginRootDirectories">*.aeplugin フォルダが置かれているルートフォルダ群。</param>
        /// <exception cref="FileNotFoundException">*.aeplugin 以下に命名規則通りの DLL ファイルがない場合に投げられます。</exception>
        internal void Load(CommandLog.Logger aLog, DirectoryInfo[] aPluginRootDirectories)
        {
            // メモ：
            // もし本関数が重くなることがあれば
            // スプラッシュロゴ表示中に "○○.aeplugin を読み込み中..." といった表示をできるように実装を変更する。

            // DLLファイルをロード
            var loadingPluginUnits = new List<PluginUnit>();
            foreach (var pluginRootDir in aPluginRootDirectories)
            {
                foreach (var pluginDir in pluginRootDir.EnumerateDirectories("*.aeplugin"))
                {
                    var baseName = pluginDir.Name.Substring(0, pluginDir.Name.Length - pluginDir.Extension.Length);
                    var dllPath = pluginDir.FullName + @"\DevKitDll";
                    if (!Directory.Exists(dllPath))
                    {
                        aLog.Error.WriteLine("プラグインフォルダ'{0}' に DevKitDll フォルダがありません。", pluginDir.FullName);
                        throw new FileNotFoundException("Not found dll error.", dllPath);
                    }
                    loadingPluginUnits.Add(new PluginUnit(new DirectoryInfo(dllPath)));
                }
            }
            PluginUnits = loadingPluginUnits.ToArray();

            // アドオンを収集
            var loadingAddons = new List<AddonInfo<IAddon>>();
            foreach (var plugin in PluginUnits)
            {
                loadingAddons.AddRange(plugin.Addons);
            }
            Addons = loadingAddons.ToArray();

            // アドオンをセットアップ
            var setupArg = new AddonSetupArg();
            foreach (var plugin in PluginUnits)
            {
                foreach (var addon in plugin.Addons)
                {
                    addon.Addon.Setup(setupArg);
                }
            }

            // ロード済
            IsLoaded = true;
        }

    }
}
