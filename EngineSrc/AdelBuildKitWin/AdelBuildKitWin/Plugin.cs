using AdelDevKit.PluginSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelBuildKitWin
{
    public class Plugin : PluginBase
    {
        public override IEnumerable<IAddon> CreateAddons()
        {
            var addons = new List<IAddon>();
            addons.Add(new VisualStudioBuilder());
            addons.Add(new CoreOsWin());
            addons.Add(new CoreGfxGl330());
            addons.Add(new CoreSndAl());
            return addons;
        }
    }
}
