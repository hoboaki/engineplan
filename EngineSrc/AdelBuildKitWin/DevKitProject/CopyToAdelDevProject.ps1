# 文字コード：UTF-8
echo "Copy to AdelDevProject ..."
$dstDir = "../DevelopResource/AdelDevProject/Plugin/AdelBuildKitWin.aeplugin/DevKitDll"
Remove-Item $dstDir -Recurse
Copy-Item ./bin/Release -destination $dstDir -recurse
echo "Copy done."
