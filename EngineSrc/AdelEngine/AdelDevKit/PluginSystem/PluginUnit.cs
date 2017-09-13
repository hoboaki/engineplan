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
            Plugins = container.GetExportedValues<IPlugin>().ToArray();

            var addons = new List<IAddon>();
            foreach (var plugin in Plugins)
            {
                addons.AddRange(plugin.CreateAddons());
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
        /// Dllから提供されたプラグインオブジェクト群。
        /// </summary>
        public IPlugin[] Plugins { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Dllから提供されたアドオンオブジェクト群。
        /// </summary>
        public IAddon[] Addons { get; private set; }
    }
}
