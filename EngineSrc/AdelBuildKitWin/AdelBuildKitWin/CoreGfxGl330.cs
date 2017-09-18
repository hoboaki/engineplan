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
    /// OpenGL 3.3 実装の CoreGfx。
    /// </summary>
    class CoreGfxGl330 : CoreGfxAddonBase
    {        
        //------------------------------------------------------------------------------
        /// <summary>
        /// Name の static 版。
        /// </summary>
        public static string StaticName { get { return nameof(AdelBuildKitWin) + "." + nameof(CoreGfxGl330); } }

        //------------------------------------------------------------------------------
        #region CoreGfxAddonBase の実装
        public override void Setup(AddonSetupArg aArg)
        {
        }

        public override string Name {  get { return StaticName; } }

        public override NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg)
        {
            return new NativeCodeBuildInfo();
        }
        
        #endregion
    }
}
