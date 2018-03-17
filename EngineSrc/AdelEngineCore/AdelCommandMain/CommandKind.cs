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
        /// ビルドして実行ファイルを作成する。
        /// </summary>
        Build,

        /// <summary>
        /// ビルドした成果物をクリーンする。
        /// </summary>
        Clean,

        /// <summary>
        /// <see cref="Clean"/> と <see cref="Build"/> をする。
        /// </summary>
        Rebuild,

        /// <summary>
        /// IDEプロジェクトファイルを更新する。
        /// </summary>
        UpdateIdeProject,
    }
}
