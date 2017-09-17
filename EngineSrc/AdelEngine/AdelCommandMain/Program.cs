using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommandMain
{
    class Program
    {
        static int Main(string[] aArgs)
        {
            // 引数解析
            var opt = new CommandLineOption();
            if (aArgs.Length == 0)
            {
                opt.PrintUsage();
                return 1;
            }
            try
            {
                // 解析開始
                opt.Load(aArgs);

                // エラー対応
                if (opt.CommandKinds.Count == 0)
                {
                    Console.Error.WriteLine("[エラー] コマンドが指定されていません。");
                    return 1;
                }
            }
            catch (Exception)
            {
                return 1;
            }

            // 実行
            Console.WriteLine("Hello AdelCommand. {0}", Assembly.GetExecutingAssembly().Location);
            return 0;
        }
    }
}
