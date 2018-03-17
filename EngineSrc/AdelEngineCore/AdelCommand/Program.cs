using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommand
{
    class Program
    {
        static int Main(string[] args)
        {
            // メモ：
            // 実行中にファイルをなるべくロックしないようにシャドウコピーする

            // 本体を実行
            var setup = new AppDomainSetup() { ShadowCopyFiles = "true" };
            var appDomain = AppDomain.CreateDomain("AdelCommand_Host", AppDomain.CurrentDomain.Evidence, setup);
            var executablePath = new FileInfo(Assembly.GetExecutingAssembly().Location).Directory.FullName + @"\Dll\AdelCommandMain.exe";
            if (!File.Exists(executablePath))
            {
                Console.Error.WriteLine("指定のファイルが見つかりません。'{0}'", executablePath);
                return 1;
            }
            return appDomain.ExecuteAssembly(executablePath, args);
        }
    }
}
