using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.PluginSystem;

namespace AdelDevKitTestsPlugin
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 特に何をするでもないアドオン。
    /// </summary>
    class SimpleAddon : AdelDevKit.PluginSystem.IAddon
    {
        string SampleProperty { get; set; } = "This is Simple Addon Property.";
        string SampleMethod() { return "This is Simple Addon Method"; }

        public void Setup(AddonSetupArg aArg)
        {
        }
    }
}
