# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

# インクルード
. "${PSScriptRoot}/../DevelopSupport/PowerShell/Env.ps1"
. "$($Env.EngineSrcRoot())/DevelopSupport/PowerShell/AdelCommand.ps1"
. "$($Env.EngineSrcRoot())/DevelopSupport/PowerShell/Msbuild.ps1"
. "$($Env.EngineSrcRoot())/DevelopSupport/PowerShell/FileUtil.ps1"

# MSBuildを使用状態にする
$msbuild = New-Object Msbuild

# ビルドキットのビルド＆コピー
$buildKitRoot = $PSScriptRoot
$configuration = "Release"
$msbuild.Execute(" /p:Configuration=${configuration} ${buildKitRoot}/DevKitProject/AdelBuildKitMac.csproj")
$srcDir = "${buildKitRoot}/DevKitProject/bin/${configuration}"
$dstDir = "${buildKitRoot}/DevelopResource/AdelDevProject/Plugin/AdelBuildKitMac.aeplugin/DevKitDll"
$FileUtil.CopyDir($srcDir, $dstDir)

# AdelCommandの実行
[AdelCommand]::Execute("-PrivateDevelopMode -ProjectDir `"${buildKitRoot}/DevelopResource/AdelDevProject`" UpdateIdeProject")
