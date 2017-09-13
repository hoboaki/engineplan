using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.PluginSystem;
using AdelDevKit.TaskSystem;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルビルダーアドオンの基底クラス。（インターフェースにデフォルト実装を加えたモノ）
    /// </summary>
    public abstract class ExecBuilderAddonBase : IExecBuilderAddon
    {
        public abstract void Setup(AddonSetupArg aArg);
        public abstract TaskSystem.Task CreateBuildTask();
    }
}
