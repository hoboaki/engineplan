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
        /// KeyValueペア。
        /// </summary>
        class KeyValuePair
        {
            public KeyValuePair(string aKey, object aValue)
            {
                Key = aKey;
                Value = aValue;
            }
            public string Key { get; private set; }
            public object Value { get; private set; }
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
                commonRootDir = new DirectoryInfo(dir.FullName + "/../AdelEngineCore/AdelEngineNative");
                devKitResDir = new DirectoryInfo(dir.FullName + "/DevKitResource");
            }

            // ファイル関連の定義
            string prefix = string.Format("{0}_{1}_{2}", aArg.ProjectSetting.Name, aArg.PlatformSetting.Name, aArg.BuildTargetSetting.Name);
            FileInfo appProjFile = new FileInfo(string.Format("{0}/{1}.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo tmpAppProjFile = new FileInfo(string.Format("{0}/{1}.tmp.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo libProjFile = new FileInfo(string.Format("{0}/{1}_AeLib.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo tmpLibProjFile = new FileInfo(string.Format("{0}/{1}_AeLib.tmp.xcodeproj", mainRootDir.FullName, prefix));
            FileInfo templateSchemeFile = new FileInfo(string.Format("{0}/XcodeTemplate/AppScheme.xcscheme", devKitResDir.FullName));
            string appFileName = string.Format("{0}", prefix);
            string libFileName = string.Format("{0}_AeLib", prefix);

            // ビルドパラメータチェック
            FileInfo infoPlistFile = null;
            {
                string keyInfoPlistPath = "InfoPlistPath";
                if (!aArg.BuilderParamInfo.BuildTargetSettingParams.ContainsKey(keyInfoPlistPath))
                {
                    aArg.Log.Error.WriteLine("必要な BuilderParam '{0}' が指定されていません。", keyInfoPlistPath);
                    throw new MessagedException();
                }
                var path = aArg.BuilderParamInfo.BuildTargetSettingParams[keyInfoPlistPath];
                infoPlistFile = new FileInfo(_SetupArg.EnvInfo.ProjectRootDir + "/" + path);
                if (!infoPlistFile.Exists)
                {
                    aArg.Log.Error.WriteLine("ファイルが見つかりません。 '{0}'", infoPlistFile.FullName);
                    throw new MessagedException();
                }
            }

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
            var macroListCommon = new List<string>();
            foreach (var macro in aArg.BuildTargetSetting.CompileMacros.OrEmptyIfNull())
            {
                macroListCommon.Add(macro);
            }
            foreach (var macro in aArg.CoreOsBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroListCommon.Add(macro);
            }
            foreach (var macro in aArg.CoreGfxBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroListCommon.Add(macro);
            }
            foreach (var macro in aArg.CoreSndBuildInfo.CompileMacros.OrEmptyIfNull())
            {
                macroListCommon.Add(macro);
            }
            var macroListDebug = macroListCommon.ToList();
            var macroListDevelop = macroListCommon.ToList();
            var macroListInspect = macroListCommon.ToList();
            var macroListPreview = macroListCommon.ToList();
            var macroListRelease = macroListCommon.ToList();
            macroListDebug.Add("AE_LIBRARY_DEBUG");
            macroListDebug.Add("DEBUG=1");
            macroListDebug.Add("$(inherited)");
            macroListDevelop.Add("AE_LIBRARY_DEVELOP");
            macroListDevelop.Add("$(inherited)");
            macroListInspect.Add("AE_LIBRARY_INSPECT");
            macroListInspect.Add("$(inherited)");
            macroListPreview.Add("AE_LIBRARY_PREVIEW");
            macroListPreview.Add("$(inherited)");
            macroListRelease.Add("AE_LIBRARY_RELEASE");
            macroListRelease.Add("$(inherited)");

            // インクルードディレクトリ列挙
            var includeDirs = new List<DirectoryInfo>();
            includeDirs.AddRange(selfNativeCodeBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreOsBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreGfxBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs.AddRange(aArg.CoreSndBuildInfo.SystemIncludeDirs.OrEmptyIfNull());
            includeDirs = includeDirs.GroupBy(x => x.FullName).Select(x => x.First()).ToList(); // 重複削除
            includeDirs.Sort((a, b) => a.FullName.CompareTo(b.FullName)); // 名前順にソート
            Func<DirectoryInfo, string[]> funcAdditionalIncludeDirectories = (aBaseDir) =>
            {
                var additionalIncludeDirectories = new List<string>();
                foreach (var includeDir in includeDirs)
                {
                    if (!includeDir.Exists)
                    {
                        aArg.Log.Error.WriteLine("インクルードディレクトリ'{0}'が存在しません。", includeDir.FullName);
                        throw new MessagedException();
                    }
                    additionalIncludeDirectories.Add("$(PROJECT_DIR)/" + FilePathUtil.ToRelativeUnixPath(aBaseDir, includeDir.FullName));
                }
                return additionalIncludeDirectories.ToArray();
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
            appSrcFiles.Add(new FileInfo(mainRootDir.FullName + "/Source/LinkOnly.m"));
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

            // フレームワーク列挙
            var linkFrameworks = new List<string>();
            linkFrameworks.Add("/System/Library/Frameworks/Cocoa.framework");

            // コンフィギュレーション列挙
            var configurationNames = new Dictionary<BuildVersion, string>();
            configurationNames.Add(BuildVersion.Debug, nameof(BuildVersion.Debug));
            configurationNames.Add(BuildVersion.Develop, nameof(BuildVersion.Develop));
            configurationNames.Add(BuildVersion.Inspect, nameof(BuildVersion.Inspect));
            configurationNames.Add(BuildVersion.Preview, nameof(BuildVersion.Preview));
            configurationNames.Add(BuildVersion.Release, nameof(BuildVersion.Release));

            // ビルド設定列挙
            // Xcodeのデフォルト値をなるべく採用しつつ都合の悪いところのみカスタマイズ
            var commonConfigurationSettings = new List<KeyValuePair>();
            commonConfigurationSettings.Add(new KeyValuePair("ALWAYS_SEARCH_USER_PATHS", "NO"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_ANALYZER_LOCALIZABILITY_NONLOCALIZED", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_ANALYZER_NONNULL", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_CXX_LANGUAGE_STANDARD", "gnu++0x"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_CXX_LIBRARY", "libc++"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_BOOL_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_CONSTANT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_DIRECT_OBJC_ISA_USAGE", "YES_ERROR"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_EMPTY_BODY", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_ENUM_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_INFINITE_RECURSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_INT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_OBJC_ROOT_CLASS", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_SUSPICIOUS_MOVE", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN_UNREACHABLE_CODE", "NO"));
            commonConfigurationSettings.Add(new KeyValuePair("CLANG_WARN__DUPLICATE_METHOD_MATCH", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("COMBINE_HIDPI_IMAGES", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("CODE_SIGN_IDENTITY", "-"));
            commonConfigurationSettings.Add(new KeyValuePair("COPY_PHASE_STRIP", "NO"));
            commonConfigurationSettings.Add(new KeyValuePair("DEBUG_INFORMATION_FORMAT", "dwarf-with-dsym"));
            commonConfigurationSettings.Add(new KeyValuePair("ENABLE_STRICT_OBJC_MSGSEND", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_C_LANGUAGE_STANDARD", "gnu99"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_NO_COMMON_BLOCKS", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_64_TO_32_BIT_CONVERSION", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_ABOUT_RETURN_TYPE", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_UNDECLARED_SELECTOR", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_UNINITIALIZED_AUTOS", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_UNUSED_FUNCTION", "NO"));
            commonConfigurationSettings.Add(new KeyValuePair("GCC_WARN_UNUSED_VARIABLE", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("PRECOMPS_INCLUDE_HEADERS_FROM_BUILT_PRODUCTS_DIR", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("RUN_CLANG_STATIC_ANALYZER", "YES"));
            commonConfigurationSettings.Add(new KeyValuePair("MACOSX_DEPLOYMENT_TARGET", "10.11"));
            commonConfigurationSettings.Add(new KeyValuePair("SDKROOT", "macosx"));

            var additionalConfigurationSetings = new Dictionary<BuildVersion, List<KeyValuePair>>();
            {
                {
                    var configurationSettings = new List<KeyValuePair>();
                    configurationSettings.Add(new KeyValuePair("ENABLE_TESTABILITY", "YES"));
                    configurationSettings.Add(new KeyValuePair("ONLY_ACTIVE_ARCH", "YES"));
                    configurationSettings.Add(new KeyValuePair("GCC_OPTIMIZATION_LEVEL", "0"));
                    configurationSettings.Add(new KeyValuePair("GCC_PREPROCESSOR_DEFINITIONS", macroListDebug));
                    configurationSettings.Add(new KeyValuePair("ZERO_LINK", "YES"));
                    additionalConfigurationSetings.Add(BuildVersion.Debug, configurationSettings);
                }
                {
                    var configurationSettings = new List<KeyValuePair>();
                    configurationSettings.Add(new KeyValuePair("ONLY_ACTIVE_ARCH", "YES"));
                    configurationSettings.Add(new KeyValuePair("GCC_PREPROCESSOR_DEFINITIONS", macroListDevelop));
                    additionalConfigurationSetings.Add(BuildVersion.Develop, configurationSettings);
                }
                {
                    var configurationSettings = new List<KeyValuePair>();
                    configurationSettings.Add(new KeyValuePair("GCC_PREPROCESSOR_DEFINITIONS", macroListInspect));
                    additionalConfigurationSetings.Add(BuildVersion.Inspect, configurationSettings);
                }
                {
                    var configurationSettings = new List<KeyValuePair>();
                    configurationSettings.Add(new KeyValuePair("GCC_PREPROCESSOR_DEFINITIONS", macroListPreview));
                    additionalConfigurationSetings.Add(BuildVersion.Preview, configurationSettings);
                }
                {
                    var configurationSettings = new List<KeyValuePair>();
                    configurationSettings.Add(new KeyValuePair("GCC_PREPROCESSOR_DEFINITIONS", macroListRelease));
                    additionalConfigurationSetings.Add(BuildVersion.Release, configurationSettings);
                }
            }

            var appConfigurationSettings = commonConfigurationSettings.ToList();
            appConfigurationSettings.Add(new KeyValuePair("HEADER_SEARCH_PATHS", funcAdditionalIncludeDirectories(appProjFile.Directory)));

            var appTargetConfigurationSettings = new List<KeyValuePair>();
            appTargetConfigurationSettings.Add(new KeyValuePair("ASSETCATALOG_COMPILER_APPICON_NAME", "AppIcon"));
            appTargetConfigurationSettings.Add(new KeyValuePair("COMBINE_HIDPI_IMAGES", "YES"));
            appTargetConfigurationSettings.Add(new KeyValuePair("INFOPLIST_FILE", "$(PROJECT_DIR)/" + FilePathUtil.ToRelativeUnixPath(appProjFile.Directory, infoPlistFile.FullName)));
            appTargetConfigurationSettings.Add(new KeyValuePair("LD_RUNPATH_SEARCH_PATHS", "$(inherited) @executable_path/../Frameworks"));
            appTargetConfigurationSettings.Add(new KeyValuePair("OTHER_LDFLAGS", "-lc++"));
            appTargetConfigurationSettings.Add(new KeyValuePair("PRODUCT_BUNDLE_IDENTIFIER", "org.MyApp"));
            appTargetConfigurationSettings.Add(new KeyValuePair("PRODUCT_NAME", "$(TARGET_NAME)"));

            var libProjConfigurationSettings = commonConfigurationSettings.ToList();
            libProjConfigurationSettings.Add(new KeyValuePair("HEADER_SEARCH_PATHS", funcAdditionalIncludeDirectories(libProjFile.Directory)));

            var libTargetConfigurationSettings = new List<KeyValuePair>();
            libTargetConfigurationSettings.Add(new KeyValuePair("EXECUTABLE_PREFIX", "lib"));
            libTargetConfigurationSettings.Add(new KeyValuePair("PRODUCT_NAME", "$(TARGET_NAME)"));

            // 言語設定
            Action<XcodeProject> funcSetupLanguage = (proj) =>
            {
                var pj = proj.Document.Project;
                pj.DevelopmentRegion = "Japanese";
                foreach (var region in pj.KnownRegions.ToList())
                {
                    pj.RemoveRegion(region);
                }
                pj.AddRegion("jp");
                pj.AddRegion("en");
                pj.AddRegion("Base");
            };

            // プロジェクト生成
            XcodeProject appProj;
            XcodeProject libProj;
            PBXTarget appTarget;
            {// lib
                var proj = new XcodeProject(tmpLibProjFile.Directory.FullName, tmpLibProjFile.Name.Replace(".xcodeproj", ""));
                funcSetupLanguage(proj);
                proj.BaseDir = tmpLibProjFile.Directory.FullName;
                proj.AddTarget(libFileName, PBXProductType.LibraryStatic);
                {
                    // Project用ConfigurationList列挙
                    foreach (var configurationName in configurationNames)
                    {
                        var configurationSettings = libProjConfigurationSettings.ToList();
                        configurationSettings.AddRange(additionalConfigurationSetings[configurationName.Key]);
                        foreach (var configurationSetting in configurationSettings)
                        {
                            proj.AddBuildConfigurationSettings(configurationName.Value, null, configurationSetting.Key, configurationSetting.Value);
                        }
                    }


                    // Target用ConfigurationList列挙
                    foreach (var configurationName in configurationNames)
                    {
                        foreach (var configurationSetting in libTargetConfigurationSettings)
                        {
                            proj.AddBuildConfigurationSettings(configurationName.Value, libFileName, configurationSetting.Key, configurationSetting.Value);
                        }
                    }
                }
                {
                    // ソース列挙
                    foreach (var srcFile in libMainSrcFiles)
                    {
                        proj.AddFile("Sources/CodeMain", srcFile.FullName, libFileName);
                    }
                    foreach (var srcFile in libCommonSrcFiles)
                    {
                        proj.AddFile("Sources/CodeCommon", srcFile.FullName, libFileName);
                    }
                }
                proj.BaseDir = ""; // 解除してからセーブしないとフルパスで記録されてしまう
                proj.Save();
                libProj = proj;
            }
            {// app
                var proj = new XcodeProject(tmpAppProjFile.Directory.FullName, tmpAppProjFile.Name.Replace(".xcodeproj", ""));
                funcSetupLanguage(proj);
                proj.BaseDir = tmpAppProjFile.Directory.FullName;
                appTarget = proj.AddTarget(appFileName, PBXProductType.Application);
                {
                    // Project用ConfigurationList列挙
                    foreach (var configurationName in configurationNames)
                    {
                        var configurationSettings = appConfigurationSettings.ToList();
                        configurationSettings.AddRange(additionalConfigurationSetings[configurationName.Key]);
                        foreach (var configurationSetting in configurationSettings)
                        {
                            proj.AddBuildConfigurationSettings(configurationName.Value, null, configurationSetting.Key, configurationSetting.Value);
                        }
                    }

                    // Target用ConfigurationList列挙
                    foreach (var configurationName in configurationNames)
                    {
                        foreach (var configurationSetting in appTargetConfigurationSettings)
                        {
                            proj.AddBuildConfigurationSettings(configurationName.Value, appFileName, configurationSetting.Key, configurationSetting.Value);
                        }
                    }
                }
                {
                    // ソース列挙
                    foreach (var srcFile in appSrcFiles)
                    {
                        proj.AddFile("Sources", srcFile.FullName, appFileName);
                    }
                    // Framework列挙
                    foreach (var framework in linkFrameworks)
                    {
                        proj.AddFramework("Frameworks", framework, appFileName);
                    }
                    // Project参照列挙
                    {
                        // 名前を正式な状態にしてから参照追加
                        var oldName = libProj.Name;
                        libProj.Name = libProjFile.Name.Replace(".xcodeproj", "");
                        proj.AddDependantProject(libProj, appFileName);
                        libProj.Name = oldName;
                    }
                }
                proj.BaseDir = ""; // 解除してからセーブしないとフルパスで記録されてしまう
                proj.Save();
                appProj = proj;
            }

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
            funcUpdateProj(appProjFile, tmpAppProjFile);

            // スキーマ作成 or 更新
            {
                // メモ
                var nativeTargetId = appProj.Document.Mapping[appTarget];
                var templateScheme = File.ReadAllText(templateSchemeFile.FullName);
                var schemeDataDir = new DirectoryInfo(appProjFile.FullName + "/xcshareddata/xcschemes");

                // 共有データフォルダがなければ作成
                if (!schemeDataDir.Exists)
                {
                    schemeDataDir.Create();
                }

                // 各ビルドバージョン毎にスキーマを作成
                foreach (var configurationName in configurationNames)
                {
                    // メモ
                    var schemeFileBaseName = string.Format("{0}__{1}", prefix, configurationName.Value);
                    FileInfo schemeFileTmp = new FileInfo(string.Format("{0}/{1}.tmp.xcscheme", schemeDataDir.FullName, schemeFileBaseName));
                    FileInfo schemeFileTarget = new FileInfo(string.Format("{0}/{1}.xcscheme", schemeDataDir.FullName, schemeFileBaseName));

                    // スキーマの内容を作成
                    string text = templateScheme;
                    text = text.Replace("__NativeTargetId__", nativeTargetId);
                    text = text.Replace("__ProjectName__", prefix);
                    text = text.Replace("__ConfigurationName__", configurationName.Value);

                    // 一時ファイルを作成
                    File.WriteAllText(schemeFileTmp.FullName, text);

                    // 必要性チェック
                    bool isNeedToUpdate = false;
                    if (!schemeFileTarget.Exists)
                    {
                        isNeedToUpdate = true;
                    }
                    else
                    {
                        var tmpText = File.ReadAllText(schemeFileTmp.FullName);
                        var targetText = File.ReadAllText(schemeFileTarget.FullName);
                        if (tmpText != targetText)
                        {
                            isNeedToUpdate = true;
                        }
                    }
                    if (!isNeedToUpdate)
                    {
                        // 更新する必要がないのでTmpを削除して終了
                        File.Delete(schemeFileTmp.FullName);
                        aArg.Log.Debug.WriteLine("Skip to update '{0}'.", schemeFileTarget.FullName);
                        continue;
                    }

                    // 更新
                    if (File.Exists(schemeFileTarget.FullName))
                    {
                        File.Delete(schemeFileTarget.FullName);
                    }
                    File.Move(schemeFileTmp.FullName, schemeFileTarget.FullName);
                }
            }
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
