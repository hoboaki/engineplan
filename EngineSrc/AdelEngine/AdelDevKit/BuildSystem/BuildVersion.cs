using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドバージョン。
    /// </summary>
    /// <remarks>
    /// 各ビルドバージョンの詳細はドキュメントを参照してください。
    /// </remarks>
    public enum BuildVersion
    {
        /// <summary>
        /// デバッグ版。
        /// </summary>
        Debug,

        /// <summary>
        /// 開発版。
        /// </summary>
        Develop,

        /// <summary>
        /// プログラム動作確認版。
        /// </summary>
        Inspect,

        /// <summary>
        /// テストプレイ版。
        /// </summary>
        Preview,

        /// <summary>
        /// リリース版。
        /// </summary>
        Release,
    }
}
