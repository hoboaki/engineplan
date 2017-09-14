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
        public string Name { get; internal set; }
        public string DisplayName { get; internal set; }
        public string BuildTargetDefault { get; internal set; }
        public BuildTarget[] BuildTargets { get; internal set; }
        public CoreLib CoreLib { get; internal set; }
    }
}
