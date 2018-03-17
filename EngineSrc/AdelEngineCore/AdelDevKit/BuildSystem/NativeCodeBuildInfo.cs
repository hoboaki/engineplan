using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ネイティブコード（c,c++,objective-cなど）をビルドする際に必要な情報。
    /// </summary>
    public class NativeCodeBuildInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンパイルが必要なソースコードファイル群。（null許容）
        /// </summary>
        /// <remarks>
        /// 拡張子によってコンパイルする方式が変わるビルダーも存在します。
        /// なるべく拡張子と使用言語を合わせるようにしてください。
        /// </remarks>
        public FileInfo[] SourceFiles { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// コード補完対象となるヘッダーファイル群。（null許容）
        /// </summary>
        public FileInfo[] AutoCompleteHeaderFiles { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 強制インクルードするヘッダーファイル群。（null許容）
        /// </summary>
        /// <remarks>
        /// プリコンパイルに対応する環境ではプリコンパイル対象にもなります。
        /// <see cref="SourceFiles"/> と同様に拡張子と使用言語を合わせるようにしてください。
        /// </remarks>
        public FileInfo[] ForceIncludeHeaderFiles { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// システムインクルード対象となるディレクトリ群。（null許容）
        /// </summary>
        /// #include <...> 形式でインクルードできるようにするフォルダをここで指定してください。
        /// ダブルコーテーションではなく "<>" で指定するものをシステムインクルードとここでは呼びます。
        public DirectoryInfo[] SystemIncludeDirs { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 静的リンクするライブラリファイル群。（null許容）
        /// </summary>
        public FileInfo[] StaticLibFiles { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 定義するプリプロセッサマクロ群。（null許容）
        /// </summary>
        public string[] CompileMacros { get; set; }
    }
}
