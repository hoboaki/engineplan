# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

# インクルード
. "$(@(Split-Path $MyInvocation.MyCommand.path))/../DevelopSupport/PowerShell/Msbuild.ps1"
. "$(@(Split-Path $MyInvocation.MyCommand.path))/../DevelopSupport/PowerShell/FileUtil.ps1"

# MSBuildを使用状態にする
$msbuild = New-Object Msbuild
$configuration = "Release"

# ビルドキットのビルド＆コピー
$msbuild.Execute(" /p:Configuration=$($configuration) ./DevKitProject/AdelBuildKitMac.csproj")
$srcDir = "./DevKitProject/bin/$($configuration)"
$dstDir = "./DevelopResource/AdelDevProject/Plugin/AdelBuildKitMac.aeplugin/DevKitDll"
[FileUtil]::CopyDir($srcDir, $dstDir)

# AdelCommandのビルド
$msbuild.Execute(" /p:Configuration=$($configuration) ../AdelEngineCore/AdelCommandMain/AdelCommandMain.csproj")
$msbuild.Execute(" /p:Configuration=$($configuration) ../AdelEngineCore/AdelCommand/AdelCommand.csproj")

# AdelCommandMain の内容をコピー
$srcDir = "../AdelEngineCore/AdelCommandMain/bin/$($configuration)"
$dstDir = "../AdelEngineCore/AdelCommand/bin/$($configuration)/Dll"
[FileUtil]::CopyDir($srcDir, $dstDir)

# AdelCommandの実行
& "mono" "../AdelEngineCore/AdelCommand/bin/$($configuration)/AdelCommand.exe" -PrivateDevelopMode -ProjectDir "./DevelopResource/AdelDevProject" UpdateIdeProject
