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
        /// 動作確認版。
        /// </summary>
        Review,

        /// <summary>
        /// 最終版。
        /// </summary>
        Final,
    }
}
