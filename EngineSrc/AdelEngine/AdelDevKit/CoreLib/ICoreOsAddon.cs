using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CoreLib
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// OSに関わる低レベル機能を提供する CoreLib アドオン。
    /// </summary>
    public interface ICoreOsAddon : PluginSystem.IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ライブラリの名前。（例：Adel.BuildKitWin.CoreOsWin）
        /// </summary>
        /// <remarks>
        /// この名前は検索のキーとして使われます。他のアドオンとは異なるユニークな名前を指定してください。
        /// </remarks>
        string Name { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ネイティブコードビルドに必要な情報を作成する。
        /// </summary>
        BuildSystem.NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg);
    }
}
