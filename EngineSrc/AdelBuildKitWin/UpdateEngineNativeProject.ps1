# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

# MSBuild定義
$vswhereExe = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
if (!(Test-Path $vswhereExe)) {
    echo "Not found vswhere."
    exit 1
}
Invoke-Expression "& `"$vswhereExe`" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath" | Set-Variable msBuildExePath
if (!($msBuildExePath)) {
    echo "Not found MSBuild."
    exit 1
}
$msBuildExe = join-path $msBuildExePath 'MSBuild\15.0\Bin\MSBuild.exe'
function ExecMsBuild ($arg) {
    $cmd = "`"$msBuildExe`"" + " " + $arg
    Invoke-Expression "& `"$msBuildExe`" $arg"
    if (!$?) {
        echo "MsBuild Failed. $LASTEXITCODE"
        exit 1
    }
}

# ビルドキットのビルド＆コピー
ExecMsBuild(" /p:Configuration=Debug ./DevKitProject/AdelBuildKitWin.csproj")
$srcDir = "./DevKitProject/bin/Debug"
$dstDir = "./DevelopResource/AdelDevProject/Plugin/AdelBuildKitWin.aeplugin/DevKitDll"
if (Test-Path $dstDir) {
    Remove-Item $dstDir -Recurse
}
Copy-Item $srcDir -destination $dstDir -recurse

# AdelCommandのビルド
ExecMsBuild(" /p:Configuration=Debug ../AdelEngineCore/AdelCommandMain/AdelCommandMain.csproj")
ExecMsBuild(" /p:Configuration=Debug ../AdelEngineCore/AdelCommand/AdelCommand.csproj")

# AdelCommandの実行
& "../AdelEngineCore/AdelCommand/bin/Debug/AdelCommand.exe" -PrivateDevelopMode -ProjectDir "./DevelopResource/AdelDevProject" UpdateIdeProject
