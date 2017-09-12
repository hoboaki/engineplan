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
    class PluginEntry
    {
        public PluginEntry(DirectoryInfo aDllDirInfo)
        {
            DllDirInfo = aDllDirInfo;

            var catalog = new DirectoryCatalog(aDllDirInfo.FullName);
            var container = new CompositionContainer(catalog);
            _Plugins = container.GetExportedValues<IPlugin>().ToArray();

            var addons = new List<IAddon>();
            foreach (var plugin in _Plugins)
            {
                addons.AddRange(plugin.CreateAddons(null));
            }
        }


        public DirectoryInfo DllDirInfo { get; private set; }
        public AppDomain _AppDomain { get; private set; }
        public IPlugin[] _Plugins;
    }
}
