// 文字コード：UTF-8
#load "./Command.csx"
#load "./Engine.csx"
#load "./Env.csx"
#load "./FileUtil.csx"
#load "./Msbuild.csx"

/// AdelCommand 実行支援クラス。
static class AdelCommand
{
    const string _Configuration = "Release";

    static bool _IsPrepared = false;

    /// ビルドやコピーなどをして実行できる状態にする。
    internal static void Prepare()
    {
        // 準備済みなら何もしない
        if (_IsPrepared)
        {
            return;
        }

        // MSBuildを使用状態にする
        var msbuild = new Msbuild();

        // AdelCommandのビルド
        msbuild.Execute($@" /p:Configuration={_Configuration} {Engine.SrcRoot()}/AdelEngineCore/AdelCommandMain/AdelCommandMain.csproj");
        msbuild.Execute($@" /p:Configuration={_Configuration} {Engine.SrcRoot()}/AdelEngineCore/AdelCommand/AdelCommand.csproj");

        // AdelCommandMain の内容をコピー
        var srcDir = $@"{Engine.SrcRoot()}/AdelEngineCore/AdelCommandMain/bin/{_Configuration}";
        var dstDir = $@"{Engine.SrcRoot()}/AdelEngineCore/AdelCommand/bin/{_Configuration}/Dll";
        FileUtil.CopyDir(srcDir, dstDir);

        // 準備OK
        _IsPrepared = true;
    }
    
    /// 実行する。
    internal static void Execute(string aArg)
    {
        // 準備してなければ準備する
        Prepare();

        // OSで分岐
        if (Env.IsMacOs)
        {
            Command.Execute("mono", $"\"{Engine.SrcRoot()}/AdelEngineCore/AdelCommand/bin/{_Configuration}/AdelCommand.exe\" {aArg}");
        }
        else
        {
            Command.Execute($"\"{Engine.SrcRoot()}/AdelEngineCore/AdelCommand/bin/{_Configuration}/AdelCommand.exe\"", aArg);
        }
    }
}
// EOF
