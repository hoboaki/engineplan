# OS に依存しない MSBuild 実行支援クラス。
class Msbuild
{
    [string] $_ExePath

    # コンストラクタ。MSBuild のパスを解決し実行できる状態にする。
    # もし MSBuild が見つからない場合はエラー終了する。
    Msbuild()
    {
        if ($Global:IsMacOS) {
            $msbuildPath = $null
            Invoke-Expression "& `"which`" MSBuild" | Set-Variable msbuildPath
            if (!(Test-Path $msbuildPath)) {
                [Console]::Error.WriteLine("Not found MSBuild.")
                exit 1
            }
            $this._ExePath = $msbuildPath
        } else {
            $vswhereExe = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
            if (!(Test-Path $vswhereExe)) {
                [Console]::Error.WriteLine("Not found vswhere.")
                exit 1
            }
            $msbuildPath = $null
            Invoke-Expression "& `"$vswhereExe`" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath" | Set-Variable msbuildPath
            if (!($msbuildPath)) {
                [Console]::Error.WriteLine("Not found MSBuild.")
                exit 1
            }
            $this._ExePath = join-path $msbuildPath 'MSBuild\15.0\Bin\MSBuild.exe'
        }
    }
    
    # MSBuild を指定のコマンドライン引数を使って実行。
    [int] Execute ([string]$aArg) {
        $exePath = $this._ExePath
        Invoke-Expression "& `"$exePath`" $aArg" | Out-Host
        if (!$?) {
            [Console]::Error.WriteLine("MSBuild Failed. $LASTEXITCODE")
            exit 1
        }
    }
}
# EOF
