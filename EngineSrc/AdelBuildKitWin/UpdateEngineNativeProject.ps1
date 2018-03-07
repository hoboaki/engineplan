# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

# MSBuild定義
$msBuildExe = "C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe"
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
ExecMsBuild(" /p:Configuration=Debug ../AdelEngine/AdelCommandMain/AdelCommandMain.csproj")
ExecMsBuild(" /p:Configuration=Debug ../AdelEngine/AdelCommand/AdelCommand.csproj")

# AdelCommandの実行
& "../AdelEngine/AdelCommand/bin/Debug/AdelCommand.exe" -PrivateDevelopMode -ProjectDir "./DevelopResource/AdelDevProject" UpdateIdeProject
