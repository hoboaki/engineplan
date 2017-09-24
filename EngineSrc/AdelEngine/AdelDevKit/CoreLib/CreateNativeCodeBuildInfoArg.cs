using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CoreLib
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// CreateNativeCodeBuildInfo に渡される引数。
    /// </summary>
    public class CreateNativeCodeBuildInfoArg
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドするビルドバージョン。
        /// </summary>
        public BuildSystem.BuildVersion BuildVersion { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行ファイルタイプ。
        /// </summary>
        public ExecutableType ExecutableType { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 開発環境モードか。
        /// </summary>
        public bool IsDevelopMode { get; internal set; }
    }
}
