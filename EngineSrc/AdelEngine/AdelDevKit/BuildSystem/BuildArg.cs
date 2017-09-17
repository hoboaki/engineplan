using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// <see cref="IBuilderAddon.CreateBuildTask(BuildArg)"/> に渡される引数。
    /// </summary>
    public class BuildArg
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーパラメータ情報。
        /// </summary>
        public BuilderParamInfo BuilderParamInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドに使う CoreOs。
        /// </summary>
        public CoreLib.ICoreOsAddon CoreOs { get; internal set; }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドに使う CoreGfx。
        /// </summary>
        public CoreLib.ICoreGfxAddon CoreGfx { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドに使う CoreSnd。
        /// </summary>
        public CoreLib.ICoreSndAddon CoreSnd { get; internal set; }
    }
}
