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
        /// ビルダーの名前。（例：AdelBuildKitWin.VisualStudioBuilder）
        /// </summary>
        /// <remarks>
        /// この名前はビルダーの検索で使われます。他のビルダーとは異なるユニークな名前を指定してください。
        ///
        /// プラットフォーム設定ファイルで指定する BuildTarget.Name はこの名前です。
        /// </remarks>
        string Name { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreOs の既定設定。
        /// </summary>
        string DefaultCoreOs { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreGfx の既定設定。
        /// </summary>
        string DefaultCoreGfx { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreSnd の既定設定。
        /// </summary>
        string DefaultCoreSnd { get; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// IDEプロジェクトファイルを更新する。
        /// </summary>
        void UpdateIdeProjectFile(BuildArg aArg);

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
