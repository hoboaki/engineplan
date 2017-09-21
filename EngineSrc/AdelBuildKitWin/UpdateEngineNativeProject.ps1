# 文字コード：UTF-8
$ErrorActionPreference = "Stop"

# MSBuild定義
$msBuildExe = "C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe"
function ExecMsBuild ($arg) {
    Start-Process -FilePath $msBuildExe -ArgumentList $arg -Wait -NoNewWindow
    #& $msBuildExe /p:Configuration=Release ./DevKitProject/AdelBuildKitWin.csproj
    if (!$?) {
        echo "MsBuild Failed. $LASTEXITCODE"
        exit 1
    }
}

# ビルドキットのビルド＆コピー
ExecMsBuild(" /p:Configuration=Release ./DevKitProject/AdelBuildKitWin.csproj")
$srcDir = "./DevKitProject/bin/Release"
$dstDir = "./DevelopResource/AdelDevProject/Plugin/AdelBuildKitWin.aeplugin/DevKitDll"
Remove-Item $dstDir -Recurse
Copy-Item $srcDir -destination $dstDir -recurse

# AdelCommandのビルド
ExecMsBuild(" /p:Configuration=Release ../AdelEngine/AdelCommandMain/AdelCommandMain.csproj")
ExecMsBuild(" /p:Configuration=Release ../AdelEngine/AdelCommand/AdelCommand.csproj")

# AdelCommandの実行
& "../AdelEngine/AdelCommand/bin/Release/AdelCommand.exe"

