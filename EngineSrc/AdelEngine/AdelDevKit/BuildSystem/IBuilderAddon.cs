using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// アプリケーションビルダーアドオン。
    /// </summary>
    public interface IBuilderAddon : PluginSystem.IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// アプリケーションをビルドするタスクを作成する。
        /// </summary>
        TaskSystem.Task CreateBuildTask(BuildArg aArg);
    }
}
