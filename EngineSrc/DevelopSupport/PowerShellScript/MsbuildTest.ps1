# テスト実行
. "./Msbuild.ps1"

$msbuild = New-Object Msbuild
$msbuild.Execute("/version")
