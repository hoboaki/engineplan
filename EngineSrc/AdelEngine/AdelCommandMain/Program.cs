using AdelDevKit;
using AdelDevKit.BuildSystem;
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
                    // ロード
                    devKit.Load(log);

                    // 実行
                    foreach (var commandKind in opt.CommandKinds)
                    {
                        switch (commandKind)
                        {
                            case CommandKind.Build:
                                log.Info.WriteLine("Build");
                                break;

                            case CommandKind.Clean:
                                log.Info.WriteLine("Clean");
                                break;

                            case CommandKind.Rebuild:
                                log.Info.WriteLine("Rebuild");
                                break;

                            case CommandKind.UpdateIdeProject:
                                ExecUpdateIdeProject(log, opt, devKit);
                                break;

                            default:
                                return ExitCodeError;
                        }
                    }
                }
            }
            catch(MessagedException)
            {
                log.Info.WriteLine("エラーが発生したため処理を中断しました。");
                return ExitCodeError;
            }
            catch(Exception exp)
            {
                log.Error.WriteLine(exp.Message);
                log.Warn.WriteLine(exp.ToString());
                log.Info.WriteLine("エラーが発生したため処理を中断しました。");
                return ExitCodeError;
            }
            finally
            {
                log.ResetConsoleColor();
            }
            return 0;
        }

        //------------------------------------------------------------------------------
        static void ExecUpdateIdeProject(Logger aLog, CommandLineOption aOpt, DevKit aDevKit)
        {
            // メモ
            var log = aLog;
            var opt = aOpt;
            var devKit = aDevKit;

            // ビルドターゲットを取得
            BuildTarget target;
            if (aOpt.BuildTargetUniqueName != null)
            {
                var buildTargets = devKit.BuildManager.BuildTargets.Where(x => x.UniqueName == aOpt.BuildTargetUniqueName);
                if (buildTargets.Count() == 0)
                {
                    log.Error.WriteLine("[エラー] '{0}' という名前の BuildTarget が存在しません。", aOpt.BuildTargetUniqueName);
                    throw new MessagedException();
                }
                System.Diagnostics.Debug.Assert(buildTargets.Count() == 1);
                target = buildTargets.First();
            }
            else if (devKit.SettingManager.PlatformSettings.Length == 1)
            {
                // プラットフォームが１つしかないならデフォルトのものを選択
                target = devKit.BuildManager.BuildTargets.Where(
                    x => x.BuildTargetSetting.Name == devKit.SettingManager.PlatformSettings[0].DefaultBuildTargetName
                    ).First();
            }
            else
            {
                log.Error.WriteLine("[エラー] {0} をコマンドラインオプションで指定してください。", nameof(aOpt.BuildTargetUniqueName));
                throw new MessagedException();
            }

            // 実行
            devKit.BuildManager.CreateIdeProjectFile(aLog, target, true);
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// エラー終了時の終了コード。
        /// </summary>
        static int ExitCodeError { get { return 1; } }
    }
}
