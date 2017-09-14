using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Setting.Platform
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// プラットフォーム設定のルート。
    /// </summary>
    public class Root
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コードネーム。（英小文字・ハイフンで構成）
        /// </summary>
        [JsonProperty()]
        public string Name { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// GUI上などで表示される名前。（分かりやすさ優先）
        /// </summary>
        [JsonProperty()]
        public string DisplayName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// デフォルトビルドターゲットの名前。
        /// </summary>
        [JsonProperty()]
        public string DefaultBuildTargetName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲットの定義。
        /// </summary>
        [JsonProperty()]
        public BuildTarget[] BuildTargets { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Coreライブラリの設定。
        /// </summary>
        [JsonProperty()]
        public CoreLib CoreLib { get; internal set; }
    }
}
