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

            AppDomainSetup setup = new AppDomainSetup();
            setup.ApplicationBase = AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            setup.ShadowCopyFiles = "true"; // DLLは自由に削除したいのでシャドーコピーを使う
            _AppDomain = AppDomain.CreateDomain(aDllFileInfo.Directory.Name, null, setup);


            var pluginType = typeof(IPlugin);
            var asm = _AppDomain.Load(aDllFileInfo.FullName);
            foreach (var t in asm.GetTypes())
            {
                if (pluginType.IsInstanceOfType(t))
                {
                    Plugins.Add(Activator.CreateInstance(t) as IPlugin);
                }
            }
        }


        public FileInfo DllFileInfo { get; private set; }
        public AppDomain _AppDomain { get; private set; }
        public List<IPlugin> Plugins = new List<IPlugin>();
    }
}
