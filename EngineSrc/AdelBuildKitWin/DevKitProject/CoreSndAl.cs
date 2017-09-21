using AdelDevKit.CoreLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.BuildSystem;
using AdelDevKit.PluginSystem;

namespace AdelBuildKitWin
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// OpenAL 実装の CoreSnd。
    /// </summary>
    class CoreSndAl : CoreSndAddonBase
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// Name の static 版。
        /// </summary>
        public static string StaticName { get { return nameof(AdelBuildKitWin) + "." + nameof(CoreSndAl); } }

        //------------------------------------------------------------------------------
        #region CoreSndAddonBase の実装
        public override void Setup(AddonSetupArg aArg)
        {
        }

        public override string Name { get { return StaticName; } }

        public override NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg)
        {
            return new NativeCodeBuildInfo();
        }

        #endregion
    }
}
