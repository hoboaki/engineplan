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
        /// ロガー。
        /// </summary>
        public CommandLog.Logger Log { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト設定。
        /// </summary>
        public Setting.Project.Root ProjectSetting { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラットフォーム設定。
        /// </summary>
        public Setting.Platform.Root PlatformSetting { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット設定。
        /// </summary>
        public Setting.Platform.BuildTarget BuildTargetSetting { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーパラメータ情報。
        /// </summary>
        public BuilderParamInfo BuilderParamInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreOs から渡された NativeCodeBuildInfo。
        /// </summary>
        public NativeCodeBuildInfo CoreOsBuildInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreGfx から渡された NativeCodeBuildInfo。
        /// </summary>
        public NativeCodeBuildInfo CoreGfxBuildInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreSnd から渡された NativeCodeBuildInfo。
        /// </summary>
        public NativeCodeBuildInfo CoreSndBuildInfo { get; internal set; }

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

        //------------------------------------------------------------------------------
        /// <summary>
        /// 開発環境モードか。
        /// </summary>
        public bool IsDevelopMode { get; internal set; }
    }
}
