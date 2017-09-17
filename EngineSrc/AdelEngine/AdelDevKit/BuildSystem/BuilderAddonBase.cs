using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.PluginSystem;
using AdelDevKit.Setting.Platform;
using AdelDevKit.TaskSystem;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルビルダーアドオンの基底クラス。（インターフェースにデフォルト実装を加えたモノ）
    /// </summary>
    public abstract class BuilderAddonBase : IBuilderAddon
    {
        public abstract void Setup(AddonSetupArg aArg);

        public abstract string Name { get; }
        public abstract Setting.Platform.CoreLib DefaultCoreLib { get; }
        public abstract TaskSystem.Task CreateBuildTask(BuildArg aArg);
        public abstract CpuBit GetCpuBit(BuilderParamInfo aParam);
        public abstract Endian GetEndian(BuilderParamInfo aParam);
    }
}
