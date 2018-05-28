:: 文字コード：UTF-8
@echo off

:: Roslyn フォルダを PATH に追加する。
set VswhereExe="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq tokens=*" %%i in (`%VswhereExe% -latest -products * -requires Microsoft.VisualStudio.Component.Roslyn.Compiler -property installationPath`) do (
  set InstallDir=%%i
)
set RoslynDir=%InstallDir%\MSBuild\15.0\Bin\Roslyn
if not exist "%RoslynDir%" (
    echo "Error: Not found Roslyn Compiler."
    exit /B 1
)
set PATH=%RoslynDir%;%PATH%
:: EOF
