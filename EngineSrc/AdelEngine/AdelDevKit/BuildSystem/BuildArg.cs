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
        /// CoreLib から渡された NativeCodeBuildInfo。
        /// </summary>
        public NativeCodeBuildInfo CoreLibBuildInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルド対象の CpuBit。
        /// </summary>
        public CpuBit CpuBit { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルド対象の Endian。
        /// </summary>
        public Endian Endian { get; internal set; }

    }
}
