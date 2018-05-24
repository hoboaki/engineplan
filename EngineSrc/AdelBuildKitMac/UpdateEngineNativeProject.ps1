# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

. "../DevelopSupport/PowerShell/Msbuild.ps1"

# MSBuildを使用状態にする
$msbuild = New-Object Msbuild

# ビルドキットのビルド＆コピー
$msbuild.Execute(" /p:Configuration=Debug ./DevKitProject/AdelBuildKitMac.csproj")
$srcDir = "./DevKitProject/bin/Debug"
$dstDir = "./DevelopResource/AdelDevProject/Plugin/AdelBuildKitMac.aeplugin/DevKitDll"
if (Test-Path $dstDir) {
    Remove-Item $dstDir -Recurse
}
Copy-Item $srcDir -destination $dstDir -recurse

# AdelCommandのビルド
$msbuild.Execute(" /p:Configuration=Debug ../AdelEngineCore/AdelCommandMain/AdelCommandMain.csproj")
$msbuild.Execute(" /p:Configuration=Debug ../AdelEngineCore/AdelCommand/AdelCommand.csproj")

# AdelCommandの実行
& "../AdelEngineCore/AdelCommand/bin/Debug/AdelCommand.exe" -PrivateDevelopMode -ProjectDir "./DevelopResource/AdelDevProject" UpdateIdeProject
