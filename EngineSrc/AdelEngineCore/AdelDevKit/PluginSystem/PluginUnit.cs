using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// １つの開発キットDLLプラグインを扱うクラス。
    /// </summary>
    /// <remarks>
    /// UnitTestをのぞき、本クラスはシャドーコピーをONにした AppDomain 上で実行されます。
    /// そのため、エディタやコマンドの実行中も DLL ファイルの上書きは可能です。
    /// </remarks>
    class PluginUnit
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aDllDirInfo">*.aeplugin/DevKitDll フォルダのパス。</param>
        public PluginUnit(DirectoryInfo aDllDirInfo)
        {
            DllDirInfo = aDllDirInfo;

            var catalog = new DirectoryCatalog(aDllDirInfo.FullName);
            var container = new CompositionContainer(catalog);
            var plugins = container.GetExportedValues<IPlugin>().ToArray();

            var addons = new List<AddonInfo<IAddon>>();
            foreach (var plugin in plugins)
            {
                var pluginInfo = new PluginInfo(
                    plugin,
                    new FileInfo(aDllDirInfo.FullName + "/" + (new FileInfo(plugin.GetType().Assembly.Location)).Name)
                    );
                addons.AddRange(plugin.CreateAddons().Select(x => new AddonInfo<IAddon>(x, pluginInfo)));
            }
            Addons = addons.ToArray();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Dllフォルダのパス。
        /// </summary>
        public DirectoryInfo DllDirInfo { get; private set; }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// Dllから提供されたアドオンオブジェクト群。
        /// </summary>
        public AddonInfo<IAddon>[] Addons { get; private set; }
    }
}
