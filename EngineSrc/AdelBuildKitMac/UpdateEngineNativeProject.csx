// 文字コード：UTF-8
#load "../DevelopSupport/CsharpScript/AdelCommand.csx"
#load "../DevelopSupport/CsharpScript/Command.csx"
#load "../DevelopSupport/CsharpScript/Engine.csx"
#load "../DevelopSupport/CsharpScript/Env.csx"
#load "../DevelopSupport/CsharpScript/FileUtil.csx"
#load "../DevelopSupport/CsharpScript/Msbuild.csx"

// MSBuildを使用状態にする
var msbuild = new Msbuild();

// ビルドキットのビルド＆コピー
var buildKitRoot = FileUtil.CurrentScriptFile().Directory.FullName;
var configuration = "Release";
msbuild.Execute($@" /p:Configuration={configuration} {buildKitRoot}/DevKitProject/AdelBuildKitMac.csproj");
var srcDir = $@"{buildKitRoot}/DevKitProject/bin/{configuration}";
var dstDir = $@"{buildKitRoot}/DevelopResource/AdelDevProject/Plugin/AdelBuildKitMac.aeplugin/DevKitDll";
FileUtil.CopyDir(srcDir, dstDir);

// AdelCommandの実行
AdelCommand.Execute($"-PrivateDevelopMode -ProjectDir \"{buildKitRoot}/DevelopResource/AdelDevProject\" UpdateIdeProject");

// EOF
