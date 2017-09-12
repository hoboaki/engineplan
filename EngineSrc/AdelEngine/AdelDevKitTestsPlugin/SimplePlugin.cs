﻿using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
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
    [Export(typeof(IPlugin))]
    public class SimplePlugin : IPlugin
    {
        public IEnumerable<IAddon> CreateAddons(DevKit aDevkit)
        {
            var addons = new List<IAddon>();
            addons.Add(new SimpleAddon());
            return addons;
        }

        string SampleProperty { get; set; } = "This is Simple Plugin Property.";
        string _SampleField = "This is Simple Plugin Field.";
        string SampleMethod() { return "This is Simple Plugin Method"; }
    }
}
