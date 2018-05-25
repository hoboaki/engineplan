# 文字コード：UTF-8

# インクルード
. "${PSScriptRoot}/Env.ps1"
. "${PSScriptRoot}/FileUtil.ps1"
. "${PSScriptRoot}/Msbuild.ps1"

# AdelCommand 実行支援クラス。
class AdelCommand
{
    static [string] $_Configuration = "Release"
    static [bool] $_IsPrepared = $False

    # ビルドやコピーなどをして実行できる状態にする。
    static [void] Prepare()
    {
        # 準備済みなら何もしない
        if ([AdelCommand]::_IsPrepared) {
            return
        }

        # MSBuildを使用状態にする
        $msbuild = New-Object Msbuild

        # AdelCommandのビルド
        $env = New-Object Env
        $msbuild.Execute(" /p:Configuration=$([AdelCommand]::_Configuration) $($env.EngineSrcRoot())/AdelEngineCore/AdelCommandMain/AdelCommandMain.csproj")
        $msbuild.Execute(" /p:Configuration=$([AdelCommand]::_Configuration) $($env.EngineSrcRoot())/AdelEngineCore/AdelCommand/AdelCommand.csproj")

        # AdelCommandMain の内容をコピー
        $srcDir = "$($env.EngineSrcRoot())/AdelEngineCore/AdelCommandMain/bin/$([AdelCommand]::_Configuration)"
        $dstDir = "$($env.EngineSrcRoot())/AdelEngineCore/AdelCommand/bin/$([AdelCommand]::_Configuration)/Dll"
        #[FileUtil]::CopyDir($srcDir, $dstDir)

        # 準備OK
        [AdelCommand]::_IsPrepared = true
    }
    
    # 実行する。
    static [void] Execute([string]$aArg)
    {
        # 準備してなければ準備する
        [AdelCommand]::Prepare()

        # OSで分岐
        $env = New-Object Env
        if ($Global:IsMacOS) {
            & "mono" "$($env.EngineSrcRoot())/AdelEngineCore/AdelCommand/bin/$([AdelCommand]::_Configuration)/AdelCommand.exe" $aArg | Out-Host
        } else {
            & "$($env.EngineSrcRoot())/AdelEngineCore/AdelCommand/bin/$([AdelCommand]::_Configuration)/AdelCommand.exe" $aArg | Out-Host
        }
    }
}

# EOF
