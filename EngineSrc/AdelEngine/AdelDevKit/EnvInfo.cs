using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// フォルダパスといった環境に関する情報を提供するクラス。
    /// </summary>
    /// <remarks>
    /// 各パスは Windows でも Mac でも動作する
    /// Unix パス形式（フォルダ区切りが'\'ではなく'\'）の形式で格納されています。
    /// 
    /// Windows API に渡す場合は DOS パス形式を要求されるものがあるため
    /// その場合は <see cref="Utility.FilePathUtil"/> を使って DOS パス形式に変換してください。
    /// </remarks>
    public class EnvInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// エンジンのルートフォルダ。
        /// </summary>
        public DirectoryInfo EngineRootDir { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクトのルートフォルダ。
        /// </summary>
        public DirectoryInfo ProjectRootDir { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト設定フォルダ。
        /// </summary>
        public DirectoryInfo ProjectSettingDir { get { return new DirectoryInfo(ProjectRootDir.FullName + "/Setting"); } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクトプラグインフォルダ。
        /// </summary>
        public DirectoryInfo ProjectPluginDir { get { return new DirectoryInfo(ProjectRootDir.FullName + "/Plugin"); } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクトアセットフォルダ。
        /// </summary>
        public DirectoryInfo ProjectAssetDir { get { return new DirectoryInfo(ProjectRootDir.FullName + "/Asset"); } }
    }
}
