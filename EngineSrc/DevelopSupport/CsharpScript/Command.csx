using System.Diagnostics;
using System.Threading;

/// シェル系コマンドの実行を支援するクラス。
static class Command
{
    /// 外部コマンドを実行。
    /// 外部コマンドが終了してから関数を抜ける。
    /// 出力系はコンソールにリダイレクト。
    /// @return 終了コード。
    /// @param aExitOnError true の場合，エラー終了したらスクリプトを止める。ほとんどが止めて欲しいので true をデフォルト値としている。
    internal static int Execute(string aCmd, string aArg = null, bool aExitOnError = true)
    {
        try
        {
            var proc = Process.Start(aCmd, aArg);
            proc.WaitForExit();
            if (aExitOnError && proc.ExitCode != 0) 
            {
                Exit(proc.ExitCode);
            }
            return proc.ExitCode;
        }
        catch (Exception exp)
        {
            Console.Error.WriteLine(exp.Message);
            Exit(1);
            return 0;
        }
    }

    /// 外部コマンドを実行し標準出力を取得する。
    /// 外部コマンドが終了してから関数を抜ける。
    /// エラー出力はコンソールにリダイレクト。
    /// もし終了コードを取得したい場合は Capture3 関数（未実装）を使用すること。
    /// @return 標準出力。
    /// @param aTrimEnd true の場合，最終文字が改行ならその改行を消す。Ruby の `cmd` と同様に使用したいケースがほとんどのためデフォルト true。
    internal static string Capture(string aCmd, string aArg = null, bool aTrimEnd = true)
    {
        try
        {
            var info = new ProcessStartInfo(aCmd, aArg);
            info.CreateNoWindow = true;
            info.UseShellExecute = false;
            info.RedirectStandardOutput = true;

            var proc = Process.Start(info);
            var result = proc.StandardOutput.ReadToEnd();
            proc.WaitForExit();
            if (proc.ExitCode != 0) 
            {
                Exit(proc.ExitCode);
            }

            // 最終改行を削除
            if (aTrimEnd)
            {
                var len = result.Length;
                if (result.LastIndexOf(Environment.NewLine) == len - Environment.NewLine.Length)
                {
                    result = result.Substring(0, len - Environment.NewLine.Length);
                }
            }

            return result;
        }
        catch (Exception exp)
        {
            Console.Error.WriteLine(exp.Message);
            Exit(1);
            return "";
        }
    }

    /// スクリプトを終了。
    internal static void Exit(int aExitCode)
    {
        Environment.Exit(aExitCode);
    }
}
