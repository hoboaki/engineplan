using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルのタイプ。
    /// </summary>
    public enum ExecutableType
    {
        /// <summary>
        /// アプリケーションタイプ。配布用。
        /// </summary>
        Application,

        /// <summary>
        /// エディタタイプ。開発用。
        /// </summary>
        Editor,
    }
}
