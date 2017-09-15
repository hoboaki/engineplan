using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Config
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドに関する設定。
    /// </summary>
    public class Build
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// 現在選択中のビルドターゲット。
        /// </summary>
        public BuildSystem.BuildTarget CurrentBuildTarget { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 現在選択中のビルドバージョン。
        /// </summary>
        public BuildSystem.BuildVersion CurrentBuildVersion { get; set; }
    }
}
