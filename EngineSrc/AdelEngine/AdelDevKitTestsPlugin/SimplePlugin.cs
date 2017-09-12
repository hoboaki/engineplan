using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit;
using AdelDevKit.PluginSystem;

namespace AdelDevKitTestsPlugin
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// テスト用プラグイン。
    /// </summary>
    public class SimplePlugin : AdelDevKit.PluginSystem.IPlugin
    {
        public IEnumerable<IAddon> CreateAddons(DevKit aDevkit)
        {
            var addons = new List<IAddon>();
            addons.Add(new SimpleAddon());
            return addons;
        }
    }
}
