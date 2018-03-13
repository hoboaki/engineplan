using AdelDevKit.PluginSystem;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelBuildKitIos
{
    [Export(typeof(IPlugin))]
    public class Plugin : PluginBase
    {
        public override IEnumerable<IAddon> CreateAddons()
        {
            var addons = new List<IAddon>();
            addons.Add(new XcodeBuilder());
            addons.Add(new CoreOsIos());
            addons.Add(new CoreGfxGles300());
            addons.Add(new CoreSndAl());
            return addons;
        }
    }
}
