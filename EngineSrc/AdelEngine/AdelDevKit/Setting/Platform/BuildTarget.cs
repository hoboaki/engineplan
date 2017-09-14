using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Setting.Platform
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドターゲット設定。
    /// </summary>
    public class BuildTarget
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コードネーム。（ロムファイル名に使用）
        /// </summary>
        public string Name { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 表示名。分かりやすさ優先。
        /// </summary>
        public string DisplayName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用するビルダーの名前。
        /// </summary>
        public string BuilderName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーに通知するパラメータ群。
        /// </summary>
        public IReadOnlyDictionary<string, object> BuilderParams { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンパイルパラメータ群。
        /// </summary>
        public string[] CompileParams { get; internal set; }
    }
}
