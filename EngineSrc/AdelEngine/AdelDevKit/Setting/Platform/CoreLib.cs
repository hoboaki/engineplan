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
    /// Coreライブラリの設定。
    /// </summary>
    public class CoreLib
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreOsライブラリの指定。（デフォルトにする場合は null）
        /// </summary>
        [JsonProperty()]
        public string CoreOs { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreGfxライブラリの指定。（デフォルトにする場合は null）
        /// </summary>
        [JsonProperty()]
        public string CoreGfx { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CoreSndライブラリの指定。（デフォルトにする場合は null）
        /// </summary>
        [JsonProperty()]
        public string CoreSnd { get; internal set; }
    }
}
