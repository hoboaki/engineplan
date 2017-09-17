using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 実行ファイルビルダーアドオン。
    /// </summary>
    public interface IBuilderAddon : PluginSystem.IAddon
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーの名前。（例：Adel.BuildKitWin.VisualStudioBuilder）
        /// </summary>
        /// <remarks>
        /// この名前はビルダーの検索で使われます。他のビルダーとは異なるユニークな名前を指定してください。
        ///
        /// プラットフォーム設定ファイルで指定する BuildTarget.Name はこの名前です。
        /// </remarks>
        string Name { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用するCoreLibの既定設定。
        /// </summary>
        Setting.Platform.CoreLib DefaultCoreLib { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// アプリケーションをビルドするタスクを作成する。
        /// </summary>
        TaskSystem.Task CreateBuildTask(BuildArg aArg);

        //------------------------------------------------------------------------------
        /// <summary>
        /// 指定のビルドパラメータでビルドする際の CpuBit を取得する。
        /// </summary>
        CpuBit GetCpuBit(BuilderParamInfo aParam);

        //------------------------------------------------------------------------------
        /// <summary>
        /// 指定のビルドパラメータでビルドする際の Endian を取得する。
        /// </summary>
        Endian GetEndian(BuilderParamInfo aParam);
    }
}
