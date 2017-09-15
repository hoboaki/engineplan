using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Setting.Project
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// プロジェクト設定。
    /// </summary>
    public class Root
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト名。
        /// </summary>
        [JsonProperty()]
        public string Name { get; internal set; }
    }
}
