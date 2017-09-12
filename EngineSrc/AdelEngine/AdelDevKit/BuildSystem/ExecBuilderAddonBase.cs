using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.TaskSystem;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルビルダーアドオンの基底クラス。（インターフェースにデフォルト実装を加えたモノ）
    /// </summary>
    public abstract class ExecBuilderAddonBase : PluginSystem.AddonBase, IExecBuilderAddon
    {
        abstract public TaskSystem.Task CreateBuildTask();
    }
}
