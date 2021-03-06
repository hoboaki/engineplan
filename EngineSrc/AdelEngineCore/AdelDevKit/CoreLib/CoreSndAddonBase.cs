﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.BuildSystem;
using AdelDevKit.PluginSystem;

namespace AdelDevKit.CoreLib
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// CoreSnd アドオンの基底クラス。（インターフェースにデフォルト実装を加えたモノ）
    /// </summary>
    public abstract class CoreSndAddonBase : ICoreSndAddon
    {
        public abstract void Setup(AddonSetupArg aArg);

        public abstract string Name { get; }
        public abstract NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg);
    }
}
