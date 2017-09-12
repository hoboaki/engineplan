using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    class PluginEntry
    {
        public PluginEntry(FileInfo aDllFileInfo)
        {
            DllFileInfo = aDllFileInfo;

            if (!File.Exists(DllFileInfo.FullName))
            {
                throw new Exception();
            }

            if (true)
            {
                AppDomainSetup setup = new AppDomainSetup();
                setup.ApplicationBase = AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
                setup.ShadowCopyFiles = "true"; // DLLは自由に削除したいのでシャドーコピーを使う
                _AppDomain = AppDomain.CreateDomain(aDllFileInfo.Directory.Name, null, setup);

                Type type = typeof(Proxy);
                Proxy proxy = (Proxy)_AppDomain.CreateInstanceAndUnwrap(Assembly.GetExecutingAssembly().FullName, type.FullName);
                proxy.Load(aDllFileInfo);
                Plugins = proxy.CreatePlugins();
            } 
            else
            {
                var proxy = new Proxy();
                proxy.Attach(Assembly.LoadFile(aDllFileInfo.FullName));
                Plugins = proxy.CreatePlugins();
            }

            foreach (var plugin in Plugins)
            {
                plugin.CreateAddons(null);
            }
        }
        public class Proxy : MarshalByRefObject
        {
            Assembly _Assembly;
            public Proxy()
            {
            }

            public void Attach(Assembly aAssembly)
            {
                _Assembly = aAssembly;
            }

            public void Load(FileInfo aDllFileInfo)
            {
                _Assembly = Assembly.LoadFile(aDllFileInfo.FullName);
            }

            public PluginBase[] CreatePlugins()
            {
                var plugins = new List<PluginBase>();
                var pluginType = typeof(PluginBase);
                foreach (var t in _Assembly.GetTypes())
                {
                    if (!pluginType.IsAssignableFrom(t))
                    {
                        continue;
                    }
                    if (t.IsAbstract || t.IsInterface)
                    {
                        continue;
                    }
                    plugins.Add(Activator.CreateInstance(t) as PluginBase);
                }
                return plugins.ToArray();
            }
        }

        public FileInfo DllFileInfo { get; private set; }
        public AppDomain _AppDomain { get; private set; }
        public PluginBase[] Plugins;
    }
}
