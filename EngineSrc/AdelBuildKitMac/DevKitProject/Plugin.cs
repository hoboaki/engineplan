using AdelDevKit.PluginSystem;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelBuildKitMac
{
    [Export(typeof(IPlugin))]
    public class Plugin : PluginBase
    {
        public override IEnumerable<IAddon> CreateAddons()
        {
            var addons = new List<IAddon>();
            addons.Add(new XcodeBuilder());
            addons.Add(new CoreOsMac());
            addons.Add(new CoreGfxGl330());
            addons.Add(new CoreSndAl());
            return addons;
        }
    }
}
