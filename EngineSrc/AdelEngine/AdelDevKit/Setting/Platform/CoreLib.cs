using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Setting.Platform
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コアライブラリの設定。
    /// </summary>
    public class CoreLib
    {
        public string CoreOs { get; internal set; }
        public string CoreGfx { get; internal set; }
        public string CoreSnd { get; internal set; }
    }
}
