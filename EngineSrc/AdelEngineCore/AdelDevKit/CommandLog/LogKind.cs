using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ログの種類
    /// </summary>
    public enum LogKind
    {
        /// <summary>
        /// 詳細なデバッグ情報。通常は見る必要がなくデバッグ時にしか確認しないような情報に使用。
        /// </summary>
        Debug,

        /// <summary>
        /// 通常レベルの情報。ログコンソールがうるさくない程度に表示する情報に使用。
        /// </summary>
        Info,

        /// <summary>
        /// 警告レベルの情報。修正対象だが致命的ではない事象に使用。
        /// </summary>
        Warn,

        /// <summary>
        /// 致命的なレベルの情報。即刻修正すべき事象の情報に使用。
        /// </summary>
        Error,
    }
}
