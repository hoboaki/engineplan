:: 文字コード：UTF-8
@echo off
cd /d %~dp0
call ..\DevelopSupport\WindowsCmd\RequireRoslyn.cmd
csi ./UpdateEngineNativeProject.csx
:: EOF
