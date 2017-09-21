:: 文字コード：UTF-8
echo off
cd /d %~dp0
powershell -ExecutionPolicy RemoteSigned -File ./CopyToAdelDevProject.ps1
