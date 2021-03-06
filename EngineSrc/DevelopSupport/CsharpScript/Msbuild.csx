// 文字コード：UTF-8
#load "./Command.csx"
#load "./Env.csx"

using System;

/// OS に依存しない MSBuild 実行支援クラス。
class Msbuild
{
    string _ExePath;

    // コンストラクタ。MSBuild のパスを解決し実行できる状態にする。
    // もし MSBuild が見つからない場合はエラー終了する。
    internal Msbuild()
    {
        if (Env.IsMacOs) 
        {
            var msbuildPath = Command.Capture("which", "MSBuild");
            if (!File.Exists(msbuildPath)) 
            {
                Console.Error.WriteLine("Error: Not found command 'MSBuild'.");
                Command.ExitAsError();
            }
            _ExePath = msbuildPath;
        }
        else 
        {
            var vswhereExe = $@"{Environment.GetEnvironmentVariable("ProgramFiles(x86)")}\Microsoft Visual Studio\Installer\vswhere.exe";
            if (!File.Exists(vswhereExe)) 
            {
                Console.Error.WriteLine("Error: Not found command 'vswhere'.");
                Command.ExitAsError();
            }
            var msbuildPath = Path.Combine(
                Command.Capture(vswhereExe, "-latest -products * -requires Microsoft.Component.MSBuild -property installationPath"),
                @"MSBuild\15.0\Bin\MSBuild.exe"
                );
            if (!File.Exists(msbuildPath))
            {
                Console.Error.WriteLine($"Error: Not found command 'MSBuild'. ({msbuildPath})");
                Command.ExitAsError();
            }
            _ExePath = msbuildPath;
        }
    }
    
    // MSBuild を指定のコマンドライン引数を使って実行。
    // エラーが発生した場合はエラー終了する。
    internal void Execute (string aArg) {
        var exitCode = Command.Execute(_ExePath, aArg, aContinueOnError: true);
        if (exitCode != 0)
        {
            Console.Error.WriteLine($@"Error: MSBuild Failed. (ExitCode: {exitCode})");
            Command.ExitAsError();
        }
    }
}
// EOF
