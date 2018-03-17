using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// <see cref="IAddon.Setup"/> に渡される引数。
    /// </summary>
    public class AddonSetupArg
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// 環境情報。
        /// </summary>
        public EnvInfo EnvInfo { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// このアドオンが含まれているプラグインのルートディレクトリ。（*.aeplugin ディレクトリ）
        /// </summary>
        public DirectoryInfo PluginDir { get; internal set; }
    }
}
