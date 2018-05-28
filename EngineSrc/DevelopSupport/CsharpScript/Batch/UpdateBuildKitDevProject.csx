// 文字コード：UTF-8
#load "../AdelCommand.csx"
#load "../Command.csx"
#load "../Engine.csx"
#load "../Env.csx"
#load "../FileUtil.csx"
#load "../Msbuild.csx"

using System.IO;

/// BuildKit フォルダにある DevProject を更新する。
static void UpdateBuildKitDevProject(DirectoryInfo aBuildKitRoot)
{
    // MSBuildを使用状態にする
    var msbuild = new Msbuild();

    // ビルドキットのビルド＆コピー
    var buildKitRoot = aBuildKitRoot.FullName;
    var buildKitName = aBuildKitRoot.Name;
    var configuration = "Release";
    msbuild.Execute($@" /p:Configuration={configuration} {buildKitRoot}/DevKitProject/{buildKitName}.csproj");
    var srcDir = $@"{buildKitRoot}/DevKitProject/bin/{configuration}";
    var dstDir = $@"{buildKitRoot}/DevelopResource/AdelDevProject/Plugin/{buildKitName}.aeplugin/DevKitDll";
    FileUtil.CopyDir(srcDir, dstDir);

    // AdelCommandの実行
    AdelCommand.Execute($"-PrivateDevelopMode -ProjectDir \"{buildKitRoot}/DevelopResource/AdelDevProject\" UpdateIdeProject");
}
// EOF
