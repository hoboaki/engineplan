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
                var dir = Utility.RootDirectoryForDevelopMode(_SetupArg.PluginDir);
                mainRootDir = new DirectoryInfo(dir.FullName + "/EngineNativeProject");
                commonRootDir = new DirectoryInfo(dir.FullName + "/../AdelEngine/AdelEngineNative");
                devKitResDir = new DirectoryInfo(dir.FullName + "/DevKitResource");
            }
            DirectoryInfo visualStudioTemplateDir = new DirectoryInfo(devKitResDir.FullName + "/VisualStudioTemplate");

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo mainSlnFile = new FileInfo(string.Format("{0}/{1}_Main.sln", mainRootDir.FullName, prefix));
            FileInfo mainProjFile = new FileInfo(string.Format("{0}/{1}_Main.vcxproj", mainRootDir.FullName, prefix));
            FileInfo commonProjFile = new FileInfo(string.Format("{0}/{1}_Common.vcxproj", commonRootDir.FullName, prefix));
            FileInfo mainSlnFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.Application.sln");
            FileInfo mainProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.Application.vcxproj");
            FileInfo commonProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.StaticLibrary.vcxproj");
            string mainSlnGuid = "{BFEF7169-E6FA-4251-AE46-1B2785573792}"; // GUIDは事前生成したものを使用
            string mainProjGuid = "{01C68E42-0D13-4A34-B624-7396F43BFCE6}"; 
            string commonProjGuid = "{7107AA3C-0ED6-4E2A-9FFA-BE2B85018B6A}";            

            // 自身用ビルドインフォ
            var selfNativeCodeBuildInfo = new NativeCodeBuildInfo();
            {
                var sourceFiles = new List<FileInfo>();
                sourceFiles.AddRange(new DirectoryInfo(commonRootDir.FullName + "/Source/ae").EnumerateFiles("*.cpp", SearchOption.AllDirectories));
                selfNativeCodeBuildInfo.SourceFiles = sourceFiles.ToArray();
            }
            {
                var autoCompleteHeaderFiles = new List<FileInfo>();
                autoCompleteHeaderFiles.AddRange(new DirectoryInfo(commonRootDir.FullName + "/Source/ae").EnumerateFiles("*.hpp", SearchOption.AllDirectories));
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
            includeDirs = includeDirs.GroupBy(x => x.FullName).Select(x => x.First()).ToList(); // 重複削除
            includeDirs.Sort((a, b) => a.FullName.CompareTo(b.FullName)); // 名前順にソート
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

            // 自動補完用ヘッダファイル列挙
            var acHeaderFiles = new List<FileInfo>();
            acHeaderFiles.AddRange(selfNativeCodeBuildInfo.AutoCompleteHeaderFiles.OrEmptyIfNull());
            acHeaderFiles.AddRange(aArg.CoreOsBuildInfo.AutoCompleteHeaderFiles.OrEmptyIfNull());
            acHeaderFiles.AddRange(aArg.CoreGfxBuildInfo.AutoCompleteHeaderFiles.OrEmptyIfNull());
            acHeaderFiles.AddRange(aArg.CoreSndBuildInfo.AutoCompleteHeaderFiles.OrEmptyIfNull());
            acHeaderFiles = acHeaderFiles.GroupBy(x => x.FullName).Select(x => x.First()).ToList(); // 重複削除
            acHeaderFiles.Sort((a, b) => a.FullName.CompareTo(b.FullName)); // 名前順にソート

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
                foreach (var srcFile in aSrcFiles)
                {
                    if (!srcFile.Exists)
                    {
                        aArg.Log.Error.WriteLine("ソースファイル'{0}'が存在しません。", srcFile.FullName);
                        throw new MessagedException();
                    }
                    string relativePath = FilePathUtil.ToRelativeDosPath(aBaseDir, srcFile.FullName);
                    stringWriter.WriteLine(string.Format("    <ClCompile Include=\"{0}\"/>", relativePath));
                }
                foreach (var headerFile in acHeaderFiles)
                {
                    if (!headerFile.Exists)
                    {
                        aArg.Log.Error.WriteLine("ヘッダーファイル'{0}'が存在しません。", headerFile.FullName);
                        throw new MessagedException();
                    }
                    string relativePath = FilePathUtil.ToRelativeDosPath(aBaseDir, headerFile.FullName);
                    stringWriter.WriteLine(string.Format("    <ClInclude Include=\"{0}\"/>", relativePath));
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
                foreach (var projInfo in aProjRefs)
                {
                    string relativePath = FilePathUtil.ToRelativeDosPath(aBaseDir, projInfo.FileInfo.FullName);
                    stringWriter.WriteLine(string.Format("    <ProjectReference Include=\"{0}\">", relativePath));
                    stringWriter.WriteLine(string.Format("      <Project>{0}</Project>", projInfo.Guid));
                    stringWriter.WriteLine(string.Format("    </ProjectReference>"));
                }
                return stringWriter.ToString();
            };

            // プロジェクト一覧
            var slnProjs = new List<VsProjInfo>();
            slnProjs.Add(new VsProjInfo() { FileInfo = mainProjFile, Guid = mainProjGuid });
            slnProjs.Add(new VsProjInfo() { FileInfo = commonProjFile, Guid = commonProjGuid });

            // 置換タグ辞書生成
            var tagAutoGenRootNamespace = "__AutoGenRootNamespace__";
            var tagAutoGenProjectGuid = "__AutoGenProjectGuid__";
            var tagAutoGenIntDir = "__AutoGenIntDir__";
            var tagAutoGenOutDir = "__AutoGenOutDir__";
            var tagAutoGenAdditionalIncludeDirectories = "__AutoGenAdditionalIncludeDirectories__";
            var tagAutoGenInsertSourceFiles = "^.*__AutoGenInsertSourceFiles__.*\n";
            var tagAutoGenInsertProjectReference = "^.*__AutoGenInsertProjectReference__.*\n";
            var tagAutoGenConfigurationBuildVersionDebug = "__AutoGenConfigurationBuildVersionDebug__";
            var tagAutoGenConfigurationBuildVersionDevelop = "__AutoGenConfigurationBuildVersionDevelop__";
            var tagAutoGenConfigurationBuildVersionReview = "__AutoGenConfigurationBuildVersionReview__";
            var tagAutoGenConfigurationBuildVersionFinal = "__AutoGenConfigurationBuildVersionFinal__";
            var tagAutoGenPlatform = "__AutoGenPlatform__";
            var autoGenReplaceTags = new Dictionary<string, string>();
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionDebug, nameof(BuildVersion.Debug));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionDevelop, nameof(BuildVersion.Develop));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionReview, nameof(BuildVersion.Review));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionFinal, nameof(BuildVersion.Final));
            autoGenReplaceTags.Add(tagAutoGenPlatform, aArg.CpuBit == CpuBit.Bit64 ? "x64" : "Win32");
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
            autoGenReplaceTagsMain.Add(tagAutoGenIntDir, FilePathUtil.ToRelativeDosPath(mainProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Obj/$(ProjectName)").FullName));
            autoGenReplaceTagsMain.Add(tagAutoGenOutDir, FilePathUtil.ToRelativeDosPath(mainProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Bin").FullName));

            // Commonプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsCommon = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsCommon.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}Common", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsCommon.Add(tagAutoGenProjectGuid, commonProjGuid);
            autoGenReplaceTagsCommon.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(commonProjFile.Directory));
            autoGenReplaceTagsCommon.Add(tagAutoGenIntDir, FilePathUtil.ToRelativeDosPath(commonProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Obj/$(ProjectName)").FullName));
            autoGenReplaceTagsCommon.Add(tagAutoGenOutDir, FilePathUtil.ToRelativeDosPath(commonProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Lib").FullName));

            // テンプレート読み込み
            var mainSlnTemplate = File.ReadAllText(mainSlnFileTemplate.FullName);
            var mainProjTemplate = File.ReadAllText(mainProjFileTemplate.FullName);
            var commonProjTemplate = File.ReadAllText(commonProjFileTemplate.FullName);

            // ファイル内容作成
            var mainSlnText = mainSlnTemplate;
            var mainProjText = mainProjTemplate;
            var commonProjText = commonProjTemplate;
            {
                // Tag置換
                foreach (var tagPair in autoGenReplaceTags)
                {
                    mainSlnText = mainSlnText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsMain)
                {
                    mainProjText = mainProjText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsCommon)
                {
                    commonProjText = commonProjText.Replace(tagPair.Key, tagPair.Value);
                }

                {// プロジェクトファイル
                    // コンパイル対象追加
                    mainProjText = Regex.Replace(mainProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(mainProjFile.Directory, mainSrcFiles), RegexOptions.Multiline);
                    commonProjText = Regex.Replace(commonProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(commonProjFile.Directory, commonSrcFiles), RegexOptions.Multiline);

                    // プロジェクト参照
                    mainProjText = Regex.Replace(mainProjText, tagAutoGenInsertProjectReference, funcProjRefs(mainProjFile.Directory, mainProjRefs), RegexOptions.Multiline);
                }

                {// ソリューションファイル
                    {// プロジェクト一覧
                        // 例
                        // Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "AeBase", "..\..\library\windows\AeBase.vcxproj", "{F7CCEEA1-49F4-475F-839A-4B75237368B6}"
                        // EndProject
                        var stringWriter = new Utf8StringWriter();
                        foreach (var slnProj in slnProjs)
                        {
                            stringWriter.WriteLine(
                                "Project(\"{0}\") = \"{1}\", \"{2}\", \"{3}\"", 
                                mainSlnGuid, 
                                Path.GetFileNameWithoutExtension(slnProj.FileInfo.Name), 
                                FilePathUtil.ToRelativeDosPath(mainSlnFile.Directory, slnProj.FileInfo.FullName),
                                slnProj.Guid
                                );
                            stringWriter.WriteLine("EndProject");
                        }
                        mainSlnText = Regex.Replace(mainSlnText, "^.*__AutoGenInsertProjectList__.*\n", stringWriter.ToString(), RegexOptions.Multiline);
                    }
                    // 構成一覧
                    {
                        // 例
                        // \t\t{D125C7DA-F98B-46CF-B3AE-2822A97C97FD}.Debug|x64.ActiveCfg = Debug|x64
                        // \t\t{D125C7DA-F98B-46CF-B3AE-2822A97C97FD}.Debug|x64.Build.0 = Debug|x64

                        var stringWriter = new Utf8StringWriter();
                        var buildVersionTags = new List<string>();
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionDebug);
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionDevelop);
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionReview);
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionFinal);
                        foreach (var slnProj in slnProjs)
                        {
                            foreach (var buildVersionTag in buildVersionTags)
                            {
                                stringWriter.WriteLine(
                                    "\t\t{0}.{1}|{2}.ActiveCfg = {1}|{2}",
                                    slnProj.Guid,
                                    autoGenReplaceTags[buildVersionTag],
                                    autoGenReplaceTags[tagAutoGenPlatform]
                                    );
                                stringWriter.WriteLine(
                                    "\t\t{0}.{1}|{2}.Build.0 = {1}|{2}",
                                    slnProj.Guid,
                                    autoGenReplaceTags[buildVersionTag],
                                    autoGenReplaceTags[tagAutoGenPlatform]
                                    );
                            }
                        }
                        mainSlnText = Regex.Replace(mainSlnText, "^.*__AutoGenInsertProjectConfigurationPlatforms__.*\n", stringWriter.ToString(), RegexOptions.Multiline);
                    }
                }
            }

            // ファイル生成
            Action<FileInfo, string> funcUpdateFile = (aFile, aText) =>
            {
                // 今あるものと同じ内容だったら何もしない
                if (aFile.Exists)
                {
                    if (aText == File.ReadAllText(aFile.FullName))
                    {
                        aArg.Log.Debug.WriteLine("Skip to update file '{0}'.", aFile.FullName);
                        return;
                    }
                }

                // 一時ファイルに書き込んでから移動
                string tmpFilePath = aFile.FullName + ".new";
                File.WriteAllText(tmpFilePath, aText);
                if (aFile.Exists)
                {
                    File.Delete(aFile.FullName);
                }
                File.Move(tmpFilePath, aFile.FullName);
                aArg.Log.Debug.WriteLine("Updated '{0}'.", aFile.FullName);

            };
            funcUpdateFile(mainProjFile, mainProjText);
            funcUpdateFile(commonProjFile, commonProjText);
            funcUpdateFile(mainSlnFile, mainSlnText);
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
