using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    public abstract class PluginBase : MarshalByRefObject, IPlugin
    {
        public abstract IEnumerable<IAddon> CreateAddons(DevKit aDevkit);
    }
}
