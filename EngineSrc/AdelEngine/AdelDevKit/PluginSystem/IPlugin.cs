using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>プラグインインターフェース。</summary>
    /// <remarks>
    /// 開発キットはPluginフォルダ以下に配置されたDLLファイルをダイナミックリンクし
    /// 本クラスを継承したクラスを作成し、アドオンを収集します。
    /// 
    /// 本クラスを継承したクラスは引数なしコンストラクタを用意してください。
    /// </remarks>
    public interface IPlugin
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグインで扱うアドオンを作成する。
        /// </summary>
        IEnumerable<IAddon> CreateAddons(DevKit aDevkit);
    }
}
