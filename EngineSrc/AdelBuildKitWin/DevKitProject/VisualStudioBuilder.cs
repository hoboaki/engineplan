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
using AdelDevKit.Utility;
using System.IO;
using AdelDevKit.CommandLog;
using System.Text.RegularExpressions;

namespace AdelBuildKitWin
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// VisualStudio 用のビルダー。
    /// </summary>
    class VisualStudioBuilder : BuilderAddonBase
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// VisualStudioプロジェクトの情報。
        /// </summary>
        class VsProjInfo
        {
            //------------------------------------------------------------------------------
            /// <summary>
            /// ファイル。
            /// </summary>
            public FileInfo FileInfo;

            //------------------------------------------------------------------------------
            /// <summary>
            /// GUID。
            /// </summary>
            public string Guid;
        }

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
            DirectoryInfo visualStudioTemplateDir = new DirectoryInfo(devKitResDir.FullName + "/VisualStudioTemplate");

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo mainProjFile = new FileInfo(string.Format("{0}/{1}_Main.vcxproj", mainRootDir.FullName, prefix));
            FileInfo commonProjFile = new FileInfo(string.Format("{0}/{1}_Common.vcxproj", commonRootDir.FullName, prefix));
            FileInfo mainProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.Application.vcxproj");
            FileInfo commonProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.StaticLibrary.vcxproj");
            string mainProjGuid = "{63f2214b-f796-4c0b-908f-c4b6e559e72b}"; // GUIDは事前生成したものを使用
            string commonProjGuid = "{b36e614f-3f96-4f39-b375-dfe703bccc23}";

            // 自身用ビルドインフォ
            var selfNativeCodeBuildInfo = new NativeCodeBuildInfo();
            {
                var sourceFiles = new List<FileInfo>();
                sourceFiles.AddRange(new DirectoryInfo(commonRootDir.FullName + "/Source/ae").EnumerateFiles("*.cpp"));
                selfNativeCodeBuildInfo.SourceFiles = sourceFiles.ToArray();
            }
            {
                var autoCompleteHeaderFiles = new List<FileInfo>();
                autoCompleteHeaderFiles.AddRange(new DirectoryInfo(commonRootDir.FullName + "/Source/ae").EnumerateFiles("*.hpp"));
                selfNativeCodeBuildInfo.AutoCompleteHeaderFiles = autoCompleteHeaderFiles.ToArray();
            }
            { 
                var systemIncludeDirs = new List<DirectoryInfo>();
                systemIncludeDirs.Add(new DirectoryInfo(commonRootDir.FullName + "/Source"));
                selfNativeCodeBuildInfo.SystemIncludeDirs = systemIncludeDirs.ToArray();
            }

            // マクロ生成
            string macroCommon = "";
            foreach (var macro in aArg.BuildTargetSetting.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreOsBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreGfxBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + ";";
            }
            foreach (var macro in aArg.CoreSndBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + ";";
            }
            string macroDebug = macroCommon + "AE_LIBRARY_DEBUG";
            string macroDevelop = macroCommon + "AE_LIBRARY_DEVELOP";
            string macroReview = macroCommon + "AE_LIBRARY_REVIEW";
            string macroFinal = macroCommon + "AE_LIBRARY_FINAL";

            // インクルードディレクトリ列挙
            var includeDirs = new List<DirectoryInfo>();
            includeDirs.AddRange(selfNativeCodeBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreOsBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreGfxBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreSndBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            Func<DirectoryInfo, string> funcAdditionalIncludeDirectories = (aBaseDir) =>
            {
                string additionalIncludeDirectories = "";
                foreach (var includeDir in includeDirs)
                {
                    if (!includeDir.Exists)
                    {
                        aArg.Log.Error.WriteLine("インクルードディレクトリ'{0}'が存在しません。", includeDir.FullName);
                        throw new MessagedException();
                    }
                    additionalIncludeDirectories += FilePathUtil.ToRelativeDosPath(aBaseDir, includeDir.FullName) + ";";
                }
                return additionalIncludeDirectories;
            };

            // ソースファイル列挙
            var srcFiles = new List<FileInfo>();
            srcFiles.AddRange(selfNativeCodeBuildInfo.SourceFiles.OrEmptyIfNull());
            srcFiles.AddRange(aArg.CoreOsBuildInfo.SourceFiles.OrEmptyIfNull());
            srcFiles.AddRange(aArg.CoreGfxBuildInfo.SourceFiles.OrEmptyIfNull());
            srcFiles.AddRange(aArg.CoreSndBuildInfo.SourceFiles.OrEmptyIfNull());

            // ソースファイル分配
            var mainSrcFiles = new List<FileInfo>();
            var commonSrcFiles = new List<FileInfo>();
            foreach (var srcFile in srcFiles)
            {
                if (srcFile.FullName.StartsWith(mainRootDir.FullName))
                {
                    mainSrcFiles.Add(srcFile);
                }
                else if (srcFile.FullName.StartsWith(commonRootDir.FullName))
                {
                    commonSrcFiles.Add(srcFile);
                }
                else
                {
                    aArg.Log.Error.WriteLine("ソースファイル'{0}'の場所が不適切です。", srcFile.FullName);
                    throw new MessagedException();
                }
            }
            Func<DirectoryInfo, List<FileInfo>, string> funcSourceFiles = (aBaseDir, aSrcFiles) =>
            {
                aSrcFiles.Sort((a, b) => a.FullName.CompareTo(b.FullName)); // abc順ソート
                var stringWriter = new Utf8StringWriter();
                stringWriter.NewLine = "\r\n";
                foreach (var srcFile in aSrcFiles)
                {
                    if (!srcFile.Exists)
                    {
                        aArg.Log.Error.WriteLine("ソースファイル'{0}'が存在しません。", srcFile.FullName);
                        throw new MessagedException();
                    }
                    string relativePath = FilePathUtil.ToRelativeDosPath(aBaseDir, srcFile.FullName);
                    stringWriter.WriteLine(string.Format("      <ClCompile Include=\"{0}\"/>", relativePath));
                }
                return stringWriter.ToString();
            };

            // プロジェクト参照
            var mainProjRefs = new List<VsProjInfo>();
            mainProjRefs.Add(new VsProjInfo() { FileInfo = commonProjFile, Guid = commonProjGuid });
            Func<DirectoryInfo, List<VsProjInfo>, string> funcProjRefs = (aBaseDir, aProjRefs) =>
            {
                aProjRefs.Sort((a, b) => a.FileInfo.FullName.CompareTo(b.FileInfo.FullName)); // abc順ソート
                var stringWriter = new Utf8StringWriter();
                stringWriter.NewLine = "\r\n";
                foreach (var projInfo in aProjRefs)
                {
                    string relativePath = FilePathUtil.ToRelativeDosPath(aBaseDir, projInfo.FileInfo.FullName);
                    stringWriter.WriteLine(string.Format("    <ProjectReference Include=\"{0}\">", relativePath));
                    stringWriter.WriteLine(string.Format("      <Project>{0}</Project>", projInfo.Guid));
                    stringWriter.WriteLine(string.Format("    </ProjectReference>"));
                }
                return stringWriter.ToString();
            };

            // 置換タグ辞書生成
            var tagAutoGenRootNamespace = "__AutoGenRootNamespace__";
            var tagAutoGenProjectGuid = "__AutoGenProjectGuid__";
            var tagAutoGenAdditionalIncludeDirectories = "__AutoGenAdditionalIncludeDirectories__";
            var tagAutoGenInsertSourceFiles = "^.*__AutoGenInsertSourceFiles__.*\n";
            var tagAutoGenInsertProjectReference = "^.*__AutoGenInsertProjectReference__.*\n";
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

            // Mainプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsMain = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsMain.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}Main", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsMain.Add(tagAutoGenProjectGuid, mainProjGuid);
            autoGenReplaceTagsMain.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(mainProjFile.Directory));

            // Commonプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsCommon = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsCommon.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}Common", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsCommon.Add(tagAutoGenProjectGuid, commonProjGuid);
            autoGenReplaceTagsCommon.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(commonProjFile.Directory));

            // テンプレート読み込み
            var mainProjTemplate = File.ReadAllText(mainProjFileTemplate.FullName);
            var commonProjTemplate = File.ReadAllText(commonProjFileTemplate.FullName);

            // ファイル内容作成
            var mainProjText = mainProjTemplate;
            var commonProjText = commonProjTemplate;
            {
                // Tag置換
                foreach (var tagPair in autoGenReplaceTagsMain)
                {
                    mainProjText = mainProjText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsCommon)
                {
                    commonProjText = commonProjText.Replace(tagPair.Key, tagPair.Value);
                }

                // コンパイル対象追加
                mainProjText = Regex.Replace(mainProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(mainProjFile.Directory, mainSrcFiles));
                commonProjText = Regex.Replace(commonProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(commonProjFile.Directory, commonSrcFiles));

                // プロジェクト参照
                mainProjText = Regex.Replace(mainProjText, tagAutoGenInsertProjectReference, funcProjRefs(mainProjFile.Directory, mainProjRefs));
            }

            // プロジェクトファイル生成
            Action<FileInfo, string> funcUpdateProj = (aProjFile, aText) =>
            {
                // 今あるものと同じ内容だったら何もしない
                if (aProjFile.Exists)
                {
                    if (aText == File.ReadAllText(aProjFile.FullName))
                    {
                        aArg.Log.Debug.WriteLine("Skip to update file '{0}'.", aProjFile.FullName);
                        return;
                    }
                }

                // 一時ファイルに書き込んでから移動
                string tmpFilePath = aProjFile.FullName + ".new";
                File.WriteAllText(tmpFilePath, aText);
                if (aProjFile.Exists)
                {
                    File.Delete(aProjFile.FullName);
                }
                File.Move(tmpFilePath, aProjFile.FullName);
                aArg.Log.Debug.WriteLine("Updated '{0}'.", aProjFile.FullName);

            };
            funcUpdateProj(mainProjFile, mainProjText);
            funcUpdateProj(commonProjFile, commonProjText);
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
