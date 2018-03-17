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

        public override void UpdateIdeProjectFile(BuildArg aArg)
        {
            // フォルダの選定
            DirectoryInfo mainRootDir = null;
            DirectoryInfo commonRootDir = null;
            DirectoryInfo devKitResDir = null;
            if (aArg.IsPrivateDevelopMode)
            {
                // 指定の名前のフォルダを探す
                var dir = Utility.RootDirectoryForDevelopMode(_SetupArg.PluginDir);
                mainRootDir = new DirectoryInfo(dir.FullName + "/EngineNativeProject");
                commonRootDir = new DirectoryInfo(dir.FullName + "/../AdelEngineCore/AdelEngineNative");
                devKitResDir = new DirectoryInfo(dir.FullName + "/DevKitResource");
            }
            DirectoryInfo visualStudioTemplateDir = new DirectoryInfo(devKitResDir.FullName + "/VisualStudioTemplate");

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo appSlnFile = new FileInfo(string.Format("{0}/{1}.sln", mainRootDir.FullName, prefix));
            FileInfo appProjFile = new FileInfo(string.Format("{0}/{1}.vcxproj", mainRootDir.FullName, prefix));
            FileInfo libMainProjFile = new FileInfo(string.Format("{0}/{1}_AeMain.vcxproj", mainRootDir.FullName, prefix));
            FileInfo libCommonProjFile = new FileInfo(string.Format("{0}/{1}_AeCommon.vcxproj", commonRootDir.FullName, prefix));
            FileInfo appSlnFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.Application.sln");
            FileInfo appProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.Application.vcxproj");
            FileInfo libMainProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.StaticLibrary.vcxproj");
            FileInfo libCommonProjFileTemplate = new FileInfo(visualStudioTemplateDir.FullName + "/AdelBuildKitWin.StaticLibrary.vcxproj");
            string appSlnGuid = "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}";
            string appProjGuid = "{F7FD653A-D72D-46B6-BEC5-3933536F768D}"; // GUIDは事前生成したものを使用
            string libMainProjGuid = "{01C68E42-0D13-4A34-B624-7396F43BFCE6}"; 
            string libCommonProjGuid = "{7107AA3C-0ED6-4E2A-9FFA-BE2B85018B6A}";            

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
            string macroInspect = macroCommon + "AE_LIBRARY_INSPECT";
            string macroPreview = macroCommon + "AE_LIBRARY_PREVIEW";
            string macroRelease = macroCommon + "AE_LIBRARY_RELEASE";

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
            var appSrcFiles = new List<FileInfo>();
            var libMainSrcFiles = new List<FileInfo>();
            var libCommonSrcFiles = new List<FileInfo>();
            appSrcFiles.Add(new FileInfo(mainRootDir.FullName + "/Source/LinkOnly.cpp"));
            foreach (var srcFile in srcFiles)
            {
                if (srcFile.FullName.StartsWith(mainRootDir.FullName))
                {
                    libMainSrcFiles.Add(srcFile);
                }
                else if (srcFile.FullName.StartsWith(commonRootDir.FullName))
                {
                    libCommonSrcFiles.Add(srcFile);
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
            var appProjRefs = new List<VsProjInfo>();
            appProjRefs.Add(new VsProjInfo() { FileInfo = libMainProjFile, Guid = libMainProjGuid });
            appProjRefs.Add(new VsProjInfo() { FileInfo = libCommonProjFile, Guid = libCommonProjGuid });
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
            slnProjs.Add(new VsProjInfo() { FileInfo = appProjFile, Guid = appProjGuid });
            slnProjs.Add(new VsProjInfo() { FileInfo = libMainProjFile, Guid = libMainProjGuid });
            slnProjs.Add(new VsProjInfo() { FileInfo = libCommonProjFile, Guid = libCommonProjGuid });

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
            var tagAutoGenConfigurationBuildVersionInspect = "__AutoGenConfigurationBuildVersionInspect__";
            var tagAutoGenConfigurationBuildVersionPreview = "__AutoGenConfigurationBuildVersionPreview__";
            var tagAutoGenConfigurationBuildVersionRelease = "__AutoGenConfigurationBuildVersionRelease__";
            var tagAutoGenPlatform = "__AutoGenPlatform__";
            var autoGenReplaceTags = new Dictionary<string, string>();
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionDebug, nameof(BuildVersion.Debug));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionDevelop, nameof(BuildVersion.Develop));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionInspect, nameof(BuildVersion.Inspect));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionPreview, nameof(BuildVersion.Preview));
            autoGenReplaceTags.Add(tagAutoGenConfigurationBuildVersionRelease, nameof(BuildVersion.Release));
            autoGenReplaceTags.Add(tagAutoGenPlatform, aArg.CpuBit == CpuBit.Bit64 ? "x64" : "Win32");
            autoGenReplaceTags.Add("__AutoGenApplicationProps__", libMainProjFile.Name);
            autoGenReplaceTags.Add("__AutoGenStaticLibraryProps__", libCommonProjFile.Name);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionDebug__", macroDebug);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionDevelop__", macroDevelop);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionInspect__", macroInspect);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionPreview__", macroPreview);
            autoGenReplaceTags.Add("__AutoGenPreprocessorDefinitionsBuildVersionRelease__", macroRelease);

            // Appプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsApp = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsApp.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsApp.Add(tagAutoGenProjectGuid, appProjGuid);
            autoGenReplaceTagsApp.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(appProjFile.Directory));
            autoGenReplaceTagsApp.Add(tagAutoGenIntDir, FilePathUtil.ToRelativeDosPath(appProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Obj/$(ProjectName)").FullName + "\\"));
            autoGenReplaceTagsApp.Add(tagAutoGenOutDir, FilePathUtil.ToRelativeDosPath(appProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Bin").FullName + "\\"));

            // LibMainプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsLibMain = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsLibMain.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}LibMain", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsLibMain.Add(tagAutoGenProjectGuid, libMainProjGuid);
            autoGenReplaceTagsLibMain.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(libMainProjFile.Directory));
            autoGenReplaceTagsLibMain.Add(tagAutoGenIntDir, FilePathUtil.ToRelativeDosPath(libMainProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Obj/$(ProjectName)").FullName + "\\"));
            autoGenReplaceTagsLibMain.Add(tagAutoGenOutDir, FilePathUtil.ToRelativeDosPath(libMainProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Lib").FullName + "\\"));

            // LibCommonプロジェクト用置換タグ辞書生成
            var autoGenReplaceTagsLibCommon = new Dictionary<string, string>(autoGenReplaceTags);
            autoGenReplaceTagsLibCommon.Add(tagAutoGenRootNamespace, string.Format("{0}{1}{2}LibCommon", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name));
            autoGenReplaceTagsLibCommon.Add(tagAutoGenProjectGuid, libCommonProjGuid);
            autoGenReplaceTagsLibCommon.Add(tagAutoGenAdditionalIncludeDirectories, funcAdditionalIncludeDirectories(libCommonProjFile.Directory));
            autoGenReplaceTagsLibCommon.Add(tagAutoGenIntDir, FilePathUtil.ToRelativeDosPath(libCommonProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Obj/$(ProjectName)").FullName + "\\"));
            autoGenReplaceTagsLibCommon.Add(tagAutoGenOutDir, FilePathUtil.ToRelativeDosPath(libCommonProjFile.Directory, new DirectoryInfo(aArg.WorkSpaceDirectory.FullName + "/$(Configuration)/Lib").FullName) + "\\");

            // テンプレート読み込み
            var appSlnTemplate = File.ReadAllText(appSlnFileTemplate.FullName);
            var appProjTemplate = File.ReadAllText(appProjFileTemplate.FullName);
            var libMainProjTemplate = File.ReadAllText(libMainProjFileTemplate.FullName);
            var libCommonProjTemplate = File.ReadAllText(libCommonProjFileTemplate.FullName);

            // ファイル内容作成
            var appSlnText = appSlnTemplate;
            var appProjText = appProjTemplate;
            var libMainProjText = libMainProjTemplate;
            var libCommonProjText = libCommonProjTemplate;
            {
                // Tag置換
                foreach (var tagPair in autoGenReplaceTags)
                {
                    appSlnText = appSlnText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsApp)
                {
                    appProjText = appProjText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsLibMain)
                {
                    libMainProjText = libMainProjText.Replace(tagPair.Key, tagPair.Value);
                }
                foreach (var tagPair in autoGenReplaceTagsLibCommon)
                {
                    libCommonProjText = libCommonProjText.Replace(tagPair.Key, tagPair.Value);
                }

                {// プロジェクトファイル
                    // コンパイル対象追加
                    appProjText = Regex.Replace(appProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(appProjFile.Directory, appSrcFiles), RegexOptions.Multiline);
                    libMainProjText = Regex.Replace(libMainProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(libMainProjFile.Directory, libMainSrcFiles), RegexOptions.Multiline);
                    libCommonProjText = Regex.Replace(libCommonProjText, tagAutoGenInsertSourceFiles, funcSourceFiles(libCommonProjFile.Directory, libCommonSrcFiles), RegexOptions.Multiline);

                    // プロジェクト参照
                    appProjText = Regex.Replace(appProjText, tagAutoGenInsertProjectReference, funcProjRefs(appProjFile.Directory, appProjRefs), RegexOptions.Multiline);
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
                                appSlnGuid, 
                                Path.GetFileNameWithoutExtension(slnProj.FileInfo.Name), 
                                FilePathUtil.ToRelativeDosPath(appSlnFile.Directory, slnProj.FileInfo.FullName),
                                slnProj.Guid
                                );
                            stringWriter.WriteLine("EndProject");
                        }
                        appSlnText = Regex.Replace(appSlnText, "^.*__AutoGenInsertProjectList__.*\n", stringWriter.ToString(), RegexOptions.Multiline);
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
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionInspect);
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionPreview);
                        buildVersionTags.Add(tagAutoGenConfigurationBuildVersionRelease);
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
                        appSlnText = Regex.Replace(appSlnText, "^.*__AutoGenInsertProjectConfigurationPlatforms__.*\n", stringWriter.ToString(), RegexOptions.Multiline);
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
            funcUpdateFile(appProjFile, appProjText);
            funcUpdateFile(libMainProjFile, libMainProjText);
            funcUpdateFile(libCommonProjFile, libCommonProjText);
            funcUpdateFile(appSlnFile, appSlnText);
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
