using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommandMain
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コマンドの種類。
    /// </summary>
    public enum CommandKind
    {
        /// <summary>
        /// ビルド。
        /// </summary>
        Build,

        /// <summary>
        /// クリーン。
        /// </summary>
        Clean,

        /// <summary>
        /// リビルド。
        /// </summary>
        Rebuild,
    }
}
