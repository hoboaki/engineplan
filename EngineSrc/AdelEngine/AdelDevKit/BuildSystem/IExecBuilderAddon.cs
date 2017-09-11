using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルビルダーアドオン。
    /// </summary>
    /// <remarks>
    /// Exec は Executable（実行ファイル） の略。長すぎたので略しました。
    /// </remarks>
    public interface IExecBuilderAddon : PluginSystem.IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// アプリケーションをビルドするタスクを作成する。
        /// </summary>
        TaskSystem.Task CreateBuildTask();
    }
}
