# OS に依存せず MSBuild を実行するためのクラス。
class Msbuild
{
    [string] $_ExePath

    # コンストラクタ。MSBuild のパスを解決し実行できる状態にする。
    Msbuild()
    {
        if ($Global:IsMacOS) {
            $msbuildPath = $null
            Invoke-Expression "& `"which`" MSBuild" | Set-Variable msbuildPath
            if (!(Test-Path $msbuildPath)) {
                Write-Output "Not found vswhere."
                exit 1
            }
            $this._ExePath = $msbuildPath
        } else {
            $vswhereExe = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
            if (!(Test-Path $vswhereExe)) {
                Write-Output "Not found vswhere."
                exit 1
            }
            $msbuildPath = $null
            Invoke-Expression "& `"$vswhereExe`" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath" | Set-Variable msbuildPath
            if (!($msbuildPath)) {
                Write-Output "Not found MSBuild."
                exit 1
            }
            $this._ExePath = join-path $msbuildPath 'MSBuild\15.0\Bin\MSBuild.exe'
        }
    }
    
    # MSBuild を指定のコマンドライン引数を使って実行。
    [void] Execute ($aArg) {
        $exePath = $this._ExePath
        Invoke-Expression "& `"$exePath`" $aArg"
        if (!$?) {
            Write-Output "MSBuild Failed. $LASTEXITCODE"
            exit 1
        }
    }
}
# EOF
