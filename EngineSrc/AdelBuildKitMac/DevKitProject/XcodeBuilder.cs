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
using Monobjc.Tools.Xcode;

namespace AdelBuildKitMac
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// Xcode 用のビルダー。
    /// </summary>
    class XcodeBuilder : BuilderAddonBase
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// 文字列ペア。
        /// </summary>
        class StringPair
        {
            public StringPair(string aKey, string aValue)
            {
                Key = aKey;
                Value = aValue;
            }
            public string Key { get; private set; }
            public string Value { get; private set; }
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
                return nameof(AdelBuildKitMac) + "." + nameof(XcodeBuilder);
            }
        }

        public override string DefaultCoreOs
        {
            get
            {
                return CoreOsMac.StaticName;
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
                commonRootDir = new DirectoryInfo(dir.FullName + "/../AdelEngine/AdelEngineNative");
                devKitResDir = new DirectoryInfo(dir.FullName + "/DevKitResource");
            }
            DirectoryInfo visualStudioTemplateDir = new DirectoryInfo(devKitResDir.FullName + "/VisualStudioTemplate");

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo appProjFile = new FileInfo(string.Format("{0}/{1}.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo libProjFile = new FileInfo(string.Format("{0}/{1}_AeLib.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo tmpLibProjFile = new FileInfo(string.Format("{0}/{1}_AeLib.tmp.xcodeproj", mainRootDir.FullName, prefix));
            string libFileName = string.Format("{0}_AeLib", prefix);

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
                macroCommon += macro + " ";
            }
            foreach (var macro in aArg.CoreOsBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + " ";
            }
            foreach (var macro in aArg.CoreGfxBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + " ";
            }
            foreach (var macro in aArg.CoreSndBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroCommon += macro + " ";
            }
            string macroDebug = macroCommon + "AE_LIBRARY_DEBUG DEBUG=1;";
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
                    additionalIncludeDirectories += "$(PROJECT_DIR)/" + FilePathUtil.ToRelativeUnixPath(aBaseDir, includeDir.FullName) + ";";
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

            // コンフィギュレーション列挙
            var configurationNames = new Dictionary<BuildVersion, string>();
            configurationNames.Add(BuildVersion.Debug, nameof(BuildVersion.Debug));
            configurationNames.Add(BuildVersion.Develop, nameof(BuildVersion.Develop));
            configurationNames.Add(BuildVersion.Review, nameof(BuildVersion.Review));
            configurationNames.Add(BuildVersion.Final, nameof(BuildVersion.Final));

            // ビルド設定列挙
            var commonConfigurationSettings = new List<StringPair>();
            commonConfigurationSettings.Add(new StringPair("CLANG_ANALYZER_NONNULL", "YES"));
            commonConfigurationSettings.Add(new StringPair("CLANG_CXX_LANGUAGE_STANDARD", "gnu++0x"));
            commonConfigurationSettings.Add(new StringPair("CLANG_WARN__DUPLICATE_METHOD_MATCH", "YES"));
            commonConfigurationSettings.Add(new StringPair("CLANG_WARN_CONSTANT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new StringPair("CLANG_WARN_ENUM_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new StringPair("CLANG_WARN_INT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new StringPair("COMBINE_HIDPI_IMAGES", "YES"));
            commonConfigurationSettings.Add(new StringPair("CODE_SIGN_IDENTITY", " - "));
            commonConfigurationSettings.Add(new StringPair("COPY_PHASE_STRIP", "NO"));
            commonConfigurationSettings.Add(new StringPair("DEBUG_INFORMATION_FORMAT", "dwarf"));
            commonConfigurationSettings.Add(new StringPair("GCC_C_LANGUAGE_STANDARD", "gnu99"));
            commonConfigurationSettings.Add(new StringPair("GCC_WARN_64_TO_32_BIT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new StringPair("GCC_WARN_ABOUT_RETURN_TYPE", "YES"));
            commonConfigurationSettings.Add(new StringPair("GCC_WARN_UNINITIALIZED_AUTOS", "YES"));
            commonConfigurationSettings.Add(new StringPair("GCC_WARN_UNUSED_VARIABLE", "YES"));
            commonConfigurationSettings.Add(new StringPair("PRECOMPS_INCLUDE_HEADERS_FROM_BUILT_PRODUCTS_DIR", "YES"));
            commonConfigurationSettings.Add(new StringPair("RUN_CLANG_STATIC_ANALYZER", "YES"));
            commonConfigurationSettings.Add(new StringPair("MACOSX_DEPLOYMENT_TARGET", "10.11"));
            commonConfigurationSettings.Add(new StringPair("SDKROOT", "macosx"));

            var additionalConfigurationSetings = new Dictionary<BuildVersion, List<StringPair>>();
            {
                {
                    var configurationSettings = new List<StringPair>();
                    configurationSettings.Add(new StringPair("GCC_OPTIMIZATION_LEVEL", "0"));
                    configurationSettings.Add(new StringPair("GCC_PREPROCESSOR_DEFINITIONS", macroDebug));
                    configurationSettings.Add(new StringPair("ZERO_LINK", "YES"));
                    additionalConfigurationSetings.Add(BuildVersion.Debug, configurationSettings);
                }
                {
                    var configurationSettings = new List<StringPair>();
                    configurationSettings.Add(new StringPair("GCC_PREPROCESSOR_DEFINITIONS", macroDevelop));
                    additionalConfigurationSetings.Add(BuildVersion.Develop, configurationSettings);
                }
                {
                    var configurationSettings = new List<StringPair>();
                    configurationSettings.Add(new StringPair("GCC_PREPROCESSOR_DEFINITIONS", macroReview));
                    additionalConfigurationSetings.Add(BuildVersion.Review, configurationSettings);
                }
                {
                    var configurationSettings = new List<StringPair>();
                    configurationSettings.Add(new StringPair("GCC_PREPROCESSOR_DEFINITIONS", macroFinal));
                    additionalConfigurationSetings.Add(BuildVersion.Final, configurationSettings);
                }
            }

            var libConfigurationSettings = commonConfigurationSettings.ToList();
            libConfigurationSettings.Add(new StringPair("HEADER_SEARCH_PATHS", funcAdditionalIncludeDirectories(libProjFile.Directory)));

            // プロジェクト生成
            var libProj = new XcodeProject(tmpLibProjFile.Directory.FullName, tmpLibProjFile.Name.Replace(".xcodeproj", ""));
            libProj.BaseDir = tmpLibProjFile.Directory.FullName;
            libProj.AddTarget(libFileName, PBXProductType.LibraryStatic);
            {
                // Project用ConfigurationList列挙
                foreach (var configurationName in configurationNames)
                {
                    var configurationSettings = libConfigurationSettings.ToList();
                    configurationSettings.AddRange(additionalConfigurationSetings[configurationName.Key]);
                    foreach (var configurationSetting in configurationSettings)
                    {
                        libProj.AddBuildConfigurationSettings(configurationName.Value, null, configurationSetting.Key, configurationSetting.Value);
                    }
                }

                // Target用ConfigurationList列挙
                foreach (var configurationName in configurationNames)
                {
                    libProj.AddBuildConfigurationSettings(configurationName.Value, libFileName, "EXECUTABLE_PREFIX", "lib");
                    libProj.AddBuildConfigurationSettings(configurationName.Value, libFileName, "PRODUCT_NAME", "$(TARGET_NAME)");
                }
            }
            {
                // ソース列挙
                foreach (var srcFile in libMainSrcFiles)
                {
                    libProj.AddFile("Source/CodeMain", srcFile.FullName, libFileName);
                }
                foreach (var srcFile in libCommonSrcFiles)
                {
                    libProj.AddFile("Source/CodeCommon", srcFile.FullName, libFileName);
                }
            }
            libProj.BaseDir = ""; // 解除してからセーブしないとフルパスで記録されてしまう
            libProj.Save();

            // 変更があったら更新
            Action<FileInfo, FileInfo> funcUpdateProj = (aProjTarget, aProjTmp) =>
            {
                // 必要性チェック
                bool isNeedToUpdate = false;
                var projDirTarget = new DirectoryInfo(aProjTarget.FullName);
                var projDirTmp = new DirectoryInfo(aProjTmp.FullName);
                var pbxprojFileTarget = new FileInfo(projDirTarget.FullName + "/project.pbxproj");
                var pbxprojFileTmp = new FileInfo(projDirTmp.FullName + "/project.pbxproj");
                if (!pbxprojFileTarget.Exists)
                {
                    isNeedToUpdate = true;
                }
                else
                {
                    var tmpText = File.ReadAllText(pbxprojFileTmp.FullName);
                    var TargetText = File.ReadAllText(pbxprojFileTarget.FullName);
                    if (tmpText != TargetText)
                    {
                        isNeedToUpdate = true;
                    }
                }
                if (!isNeedToUpdate)
                {
                    // 更新する必要がないのでTmpを削除して終了
                    Directory.Delete(projDirTmp.FullName, true);
                    aArg.Log.Debug.WriteLine("Skip to update '{0}'.", aProjTarget.FullName);
                    return;
                }

                // 新規ならリネームして終了
                if (!Directory.Exists(aProjTarget.FullName))
                {
                    Directory.Move(projDirTmp.FullName, projDirTarget.FullName);
                }
                else
                {
                    // pbxproj のみ更新
                    if (File.Exists(pbxprojFileTarget.FullName))
                    {
                        File.Delete(pbxprojFileTarget.FullName);
                    }
                    File.Move(pbxprojFileTmp.FullName, pbxprojFileTarget.FullName);

                    // Tmpを削除
                    Directory.Delete(projDirTmp.FullName, true);
                }
                aArg.Log.Debug.WriteLine("Updated '{0}'.", aProjTarget.FullName);
            };
            funcUpdateProj(libProjFile, tmpLibProjFile);
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
