using AdelDevKit;
using AdelDevKit.CommandLog;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommandMain
{
    class Program
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// エントリーポイント。
        /// </summary>
        static int Main(string[] aArgs)
        {
            // 引数解析
            var opt = new CommandLineOption();
            if (aArgs.Length == 0)
            {
                opt.PrintUsage();
                return ExitCodeError;
            }
            try
            {
                // 解析開始
                opt.Load(aArgs);

                // エラー対応
                if (opt.CommandKinds.Count == 0)
                {
                    Console.Error.WriteLine("[エラー] コマンドが指定されていません。");
                    return ExitCodeError;
                }
            }
            catch (Exception)
            {
                return ExitCodeError;
            }

            // オブジェクト生成
            var log = new AdelDevKit.CommandLog.ConsoleLogger();
            try
            {
                using (var devKit = new DevKit(log, new DirectoryInfo(opt.ProjectDir)))
                {
                    devKit.Load(log);
                }
            }
            catch(MessagedException)
            {
                log.Error.WriteLine("エラーが発生したため処理を中断しました。");
                return ExitCodeError;
            }
            catch(Exception exp)
            {
                log.Error.WriteLine(exp.Message);
                log.Warn.WriteLine(exp.ToString());
                log.Error.WriteLine("エラーが発生したため処理を中断しました。");
                return ExitCodeError;
            }

            // 実行
            Console.WriteLine("Hello AdelCommand. {0}", Assembly.GetExecutingAssembly().Location);
            return 0;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// エラー終了時の終了コード。
        /// </summary>
        static int ExitCodeError { get { return 1; } }
    }
}
