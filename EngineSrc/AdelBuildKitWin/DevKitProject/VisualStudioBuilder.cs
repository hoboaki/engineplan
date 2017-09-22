using AdelDevKit.BuildSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit;
using AdelDevKit.PluginSystem;
using AdelDevKit.Setting.Platform;
using AdelDevKit.TaskSystem;
using System.IO;

namespace AdelBuildKitWin
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// VisualStudio 用のビルダー。
    /// </summary>
    class VisualStudioBuilder : BuilderAddonBase
    {
        //------------------------------------------------------------------------------
        #region BuilderAddonBase の実装
        public override void Setup(AddonSetupArg aArg)
        {
            _SetupArg = aArg;
        }
        AddonSetupArg _SetupArg;

        public override string Name
        {
            get
            {
                return nameof(AdelBuildKitWin) + "." + nameof(VisualStudioBuilder);
            }
        }

        public override string DefaultCoreOs
        {
            get
            {
                return CoreOsWin.StaticName;
            }
        }

        public override string DefaultCoreGfx
        {
            get
            {
                return CoreGfxGl330.StaticName;
            }
        }

        public override string DefaultCoreSnd
        {
            get
            {
                return CoreSndAl.StaticName;
            }
        }

        public override void CreateIdeProjectFile(BuildArg aArg)
        {
            // フォルダの選定
            DirectoryInfo mainRootDir = null;
            DirectoryInfo commonRootDir = null;
            DirectoryInfo devKitResDir = null;
            if (aArg.IsDevelopMode)
            {
                // 指定の名前のフォルダを探す
                var dir = _SetupArg.PluginDir.Parent;
                while (dir != null && dir.Name != "AdelBuildKitWin")
                {
                    dir = dir.Parent;
                }
                mainRootDir = new DirectoryInfo(dir.FullName + "/EngineNativeProject");
                commonRootDir = new DirectoryInfo(dir.FullName + "/../AdelEngine/AdelEngineNative");
                devKitResDir = new DirectoryInfo(dir.FullName + "/DevKitResource");
            }

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo mainProjFile = new FileInfo(string.Format("{0}/{1}_Main.vcxproj", mainRootDir.FullName, prefix));
            FileInfo mainPropsFile = new FileInfo(string.Format("{0}/{1}_Main.props", mainRootDir.FullName, prefix));
            FileInfo commonProjFile = new FileInfo(string.Format("{0}/{1}_Common.vcxproj", commonRootDir.FullName, prefix));
            FileInfo commonPropsFile = new FileInfo(string.Format("{0}/{1}_Common.props", commonRootDir.FullName, prefix));
            FileInfo mainProjFileTmp = new FileInfo(mainProjFile.FullName + ".tmp");
            FileInfo mainPropsFileTmp = new FileInfo(mainPropsFile.FullName + ".tmp");
            FileInfo commonProjFileTmp = new FileInfo(commonProjFile.FullName + ".tmp");
            FileInfo commonPropsFileTmp = new FileInfo(commonPropsFile.FullName + ".tmp");
            string mainProjGuid = "{63f2214b-f796-4c0b-908f-c4b6e559e72b}"; // GUIDは事前生成したものを使用
            string commonProjGuid = "{b36e614f-3f96-4f39-b375-dfe703bccc23}";

            // マクロ生成
            string macroCommon = "";
            foreach (var macro in aArg.BuildTargetSetting.CompileMacros)
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreOsBuildInfo.CompileMacros)
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreGfxBuildInfo.CompileMacros)
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreSndBuildInfo.CompileMacros)
            {
                macroCommon += macro + ";";
            }
            string macroDebug = macroCommon + "AE_LIBRARY_DEBUG";
            string macroDevelop = macroCommon + "AE_LIBRARY_DEVELOP";
            string macroReview = macroCommon + "AE_LIBRARY_REVIEW";
            string macroFinal = macroCommon + "AE_LIBRARY_FINAL";

            // 置換タグ辞書生成
            var tagAutoGenRootNamespace = "__AutoGenRootNamespace__";
            var tagAutoGenProjectGuid = "__AutoGenProjectGuid__";            
            var autoGenReplaceTags = new Dictionary<string, string>();
            autoGenReplaceTags.Add("__AutoGenConfigurationBuildVersionDebug__", nameof(BuildVersion.Debug));
            autoGenReplaceTags.Add("__AutoGenConfigurationBuildVersionDevelop__", nameof(BuildVersion.Develop));
            autoGenReplaceTags.Add("__AutoGenConfigurationBuildVersionReview__", nameof(BuildVersion.Review));
            autoGenReplaceTags.Add("__AutoGenConfigurationBuildVersionFinal__", nameof(BuildVersion.Final));
            autoGenReplaceTags.Add("__AutoGenApplicationProps__", mainProjFile.Name);
            autoGenReplaceTags.Add("__AutoGenStaticLibraryProps__", commonProjFile.Name);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionDebug__", macroDebug);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionDevelop__", macroDevelop);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionReview__", macroReview);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionFinal__", macroFinal);

            var autoGenReplaceTagsMain = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTags.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}Main", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTags.Add(tagAutoGenProjectGuid, mainProjGuid);

            var autoGenReplaceTagsCommon = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTags.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}Common", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTags.Add(tagAutoGenProjectGuid, commonProjGuid);


        }

        public override AdelDevKit.TaskSystem.Task CreateBuildTask(BuildArg aArg)
        {
            throw new NotImplementedException();
        }

        public override CpuBit GetCpuBit(BuilderParamInfo aParam)
        {
            return CpuBit.Bit64;
        }

        public override Endian GetEndian(BuilderParamInfo aParam)
        {
            return Endian.LittleEndian;
        }

        #endregion
    }
}
