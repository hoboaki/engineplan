﻿using AdelDevKit.CoreLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.BuildSystem;
using AdelDevKit.PluginSystem;

namespace AdelBuildKitWin
{
    class CoreGfxGl330 : CoreGfxAddonBase
    {        
        public static string StaticName { get { return nameof(AdelBuildKitWin) + "." + nameof(CoreGfxGl330); } }

        public override string Name
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public override NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg)
        {
            throw new NotImplementedException();
        }

        public override void Setup(AddonSetupArg aArg)
        {
            throw new NotImplementedException();
        }
    }
}
