using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// アドオン（追加機能）の基底インターフェース。
    /// </summary>
    public interface IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// アドオンを使える状態にする。
        /// </summary>
        /// <remarks>
        /// 重い処理はコンストラクタではなく本関数内で行ってください。
        /// 
        /// この関数が呼ばれている時点で、既に全アドオンの作成は終わっています。
        /// ただし、それらアドオンのセットアップは終わっていない可能性があるのでその点は注意してください。
        /// </remarks>
        void Setup(AddonSetupArg aArg);
    }
}
