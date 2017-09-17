using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルダーアドオンを使ってビルドするクラス。
    /// </summary>
    public class Builder
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal Builder(PluginSystem.AddonInfo<IBuilderAddon> aAddon)
        {
            Addon = aAddon;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用するビルダーアドオン。
        /// </summary>
        internal PluginSystem.AddonInfo<IBuilderAddon> Addon { get; private set; }
    }
}
