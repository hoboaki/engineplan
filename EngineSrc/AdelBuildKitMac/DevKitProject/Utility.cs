using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelBuildKitMac
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 便利関数群。
    /// </summary>
    static class Utility
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// Main枠のネイティブコードフォルダを取得。
        /// </summary>
        public static DirectoryInfo MainNativeCodeDirectory(DirectoryInfo aPluginDir, bool aIsDevelopMode)
        {
            if (aIsDevelopMode)
            {
                return new DirectoryInfo(RootDirectoryForDevelopMode(aPluginDir).FullName + "/EngineNativeProject/Source");
            }
            else
            {
                return new DirectoryInfo(aPluginDir + "/NativeCode");
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Common枠のネイティブコードフォルダを取得。
        /// </summary>
        public static DirectoryInfo CommonNativeCodeDirectory(DirectoryInfo aPluginDir, bool aIsDevelopMode)
        {
            if (aIsDevelopMode)
            {
                return new DirectoryInfo(RootDirectoryForDevelopMode(aPluginDir).FullName + "/../AdelEngineCore/AdelEngineNative/Source");
            }
            else
            {
                return new DirectoryInfo(aPluginDir + "/NativeCode");
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 開発モード用のルートディレクトリを取得。
        /// </summary>
        public static DirectoryInfo RootDirectoryForDevelopMode(DirectoryInfo aPluginDir)
        {
            var dir = aPluginDir.Parent;
            while (dir != null && dir.Name != "AdelBuildKitMac")
            {
                dir = dir.Parent;
            }
            System.Diagnostics.Debug.Assert(dir != null);
            return dir;
        }
    }
}
