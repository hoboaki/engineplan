using AdelDevKit.CoreLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit.BuildSystem;
using AdelDevKit.PluginSystem;
using System.IO;

namespace AdelBuildKitMac
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// OpenGL 3.3 実装の CoreGfx。
    /// </summary>
    class CoreGfxGl330 : CoreGfxAddonBase
    {        
        //------------------------------------------------------------------------------
        /// <summary>
        /// Name の static 版。
        /// </summary>
        public static string StaticName { get { return nameof(AdelBuildKitMac) + "." + nameof(CoreGfxGl330); } }

        //------------------------------------------------------------------------------
        #region CoreGfxAddonBase の実装
        public override void Setup(AddonSetupArg aArg)
        {
            _SetupArg = aArg;
        }
        AddonSetupArg _SetupArg;

        public override string Name {  get { return StaticName; } }

        public override NativeCodeBuildInfo CreateNativeCodeBulidInfo(CreateNativeCodeBuildInfoArg aArg)
        {
            var obj = new NativeCodeBuildInfo();
            {
                var srcFiles = new List<FileInfo>();
                var headerFiles = new List<FileInfo>();
                var includeDirs = new List<DirectoryInfo>();

                var mainDirRoot = Utility.MainNativeCodeDirectory(_SetupArg.PluginDir, aArg.IsPrivateDevelopMode);
                var commonDirRoot = Utility.CommonNativeCodeDirectory(_SetupArg.PluginDir, aArg.IsPrivateDevelopMode);
                var dirs = new List<DirectoryInfo>();
                dirs.Add(new DirectoryInfo(mainDirRoot.FullName + "/ae_mac_gl330"));
                dirs.Add(new DirectoryInfo(commonDirRoot.FullName + "/ae_opengl"));
                foreach (var dir in dirs)
                {
                    srcFiles.AddRange(dir.EnumerateFiles("*.c", SearchOption.AllDirectories));
                    srcFiles.AddRange(dir.EnumerateFiles("*.cpp", SearchOption.AllDirectories));
                    headerFiles.AddRange(dir.EnumerateFiles("*.h", SearchOption.AllDirectories));
                    headerFiles.AddRange(dir.EnumerateFiles("*.hpp", SearchOption.AllDirectories));
                }
                includeDirs.Add(mainDirRoot);
                includeDirs.Add(commonDirRoot);

                obj.SourceFiles = srcFiles.ToArray();
                obj.AutoCompleteHeaderFiles = headerFiles.ToArray();
                obj.SystemIncludeDirs = includeDirs.ToArray();
            }
            return obj;
        }
        
        #endregion
    }
}
