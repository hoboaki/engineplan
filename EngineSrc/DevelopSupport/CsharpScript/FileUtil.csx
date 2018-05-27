// 文字コード：UTF-8
#load "./Command.csx"

using System.IO;

/// ファイル操作便利機能。
static class FileUtil
{
    /// 呼び出し元のファイル情報を取得する。
    /// この関数を呼び出した csx ファイルの情報が得られます。
    internal static FileInfo CurrentScriptFile([System.Runtime.CompilerServices.CallerFilePath] string aFileName = null)
    {
        return new FileInfo(aFileName);
    }

    /// aFrom 以下にあるファイル＆ディレクトリを aTo 以下にコピーする。
    /// コピー先にファイルやディレクトリがあれば消してからコピーする。
    internal static void CopyDir(string aFrom, string aTo)
    {
        // コピー元確認
        var from = new DirectoryInfo(aFrom);
        if (!from.Exists) 
        {
            Console.Error.WriteLine($@"Error: '{aFrom}' is not exists.");
            Command.ExitAsError();
        }

        // コピー先が存在したら削除
        var to = new DirectoryInfo(aTo);
        try
        {
            if (File.Exists(to.FullName))
            {
                File.Delete(to.FullName);
            }
            if (Directory.Exists(to.FullName))
            {
                Directory.Delete(to.FullName, recursive: true);
            }
        }
        catch (Exception exp)
        {
            Console.Error.WriteLine($@"Error: Can't delete '{aTo}'.");
            Command.ExitAsError();
        }

        // コピー
        Action<DirectoryInfo, DirectoryInfo> copy = null;
        copy = (fromDir, toDir) =>
        {
            foreach (var dir in fromDir.GetDirectories())
            {
                copy(dir, toDir.CreateSubdirectory(dir.Name));
            }
            foreach (var file in fromDir.GetFiles())
            {
                file.CopyTo(Path.Combine(toDir.FullName, file.Name));
            }
        };
        try
        {
            copy(from, to);
        }
        catch (Exception exp)
        {
            Console.Error.WriteLine(exp.Message);
            Console.Error.WriteLine($@"Error: Copy failed. (From:'{aFrom}', To:'{aTo}')");
            Command.ExitAsError();
        }
    }
}
// EOF
