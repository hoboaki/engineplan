using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクの分類。
    /// </summary>
    enum TaskCategory
    {
        /// <summary>
        /// バージョン管理システム処理。
        /// </summary>
        VcsProcess,

        /// <summary>
        /// バッチ処理。
        /// </summary>
        BatchProcess,

        /// <summary>
        /// アセットビルド。
        /// </summary>
        AssetBuild,

        /// <summary>
        /// 実行ファイルビルド。
        /// </summary>
        ExecutableFileBuild,
    }
}
