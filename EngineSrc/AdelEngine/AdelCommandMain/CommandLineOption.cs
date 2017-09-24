using AdelDevKit.BuildSystem;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommandMain
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コマンドラインオプション。
    /// </summary>
    public class CommandLineOption
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コマンドライン引数からオプションをロードする。
        /// </summary>
        /// <exception cref="Exception">解析中にエラーが発生したら投げられる。</exception>
        public void Load(string[] aArgs)
        {
            // だいぶ泥臭い実装になってます。

            // 共通変数とアクションの用意
            int argIdx = 0;
            string option = null;
            string lastArg = null;
            Func<string> nextArg = () =>
            {
                if (argIdx == aArgs.Length)
                {
                    Console.Error.WriteLine("[エラー] オプション'{0}'に対して引数が足りません。", option);
                    throw new Exception();
                }
                lastArg = aArgs[argIdx];
                ++argIdx;
                if (option == null)
                {
                    option = lastArg;
                }
                return lastArg;
            };
            Action invalidEnumOptionError = () =>
            {
                Console.Error.WriteLine("[エラー] オプション'{0}'に対してパラメータ'{1}'は無効です。", option, lastArg);
                throw new Exception();
            };

            // パースしていく
            while (argIdx < aArgs.Length)
            {
                option = null;
                switch (nextArg())
                {
                    case "-" + nameof(BuildTargetUniqueName):
                        BuildTargetUniqueName = nextArg();
                        break;

                    case "-" + nameof(BuildVersion):
                        {
                            BuildVersion tmp;
                            if (!Enum.TryParse<BuildVersion>(nextArg(), out tmp))
                            {
                                invalidEnumOptionError();
                            }
                            BuildVersion = tmp;
                        }
                        break;

                    case "-" + nameof(ProjectDir):
                        {
                            ProjectDir = nextArg();
                        }
                        break;

                    case "-" + nameof(PrivateDevelopMode):
                        PrivateDevelopMode = true;
                        break;

                    default:
                        {
                            // コマンド達
                            CommandKind tmp;
                            if (!Enum.TryParse<CommandKind>(lastArg, out tmp))
                            {
                                Console.Error.WriteLine("[エラー] '{0}'というコマンドは存在しません。", lastArg);
                                throw new Exception();
                            }
                            CommandKinds.Add(tmp);
                            break;
                        }
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使い方を取得。
        /// </summary>
        public void PrintUsage()
        {
            var writer = new StringWriter();
            writer.WriteLine("Usage: AdelCommand.exe [options] [commands]");
            writer.WriteLine("Options:");
            writer.WriteLine("    -{0}: Set build target for build.", nameof(BuildTargetUniqueName));
            writer.WriteLine("        If platform  count is one, you can skip to set this option.");
            writer.WriteLine("        Format is \"PlatformName + '/' + BuildTargetName.");
            writer.WriteLine("        Ex. \"MyPlatform/Product\" for PlatformName=\"MyPlatform\" BuildTargetName=\"Product\"");
            writer.WriteLine("    -{0}: Set build version for build.", nameof(BuildVersion));
            {
                writer.Write("        [");
                BuildVersion[] versions = { BuildVersion.Debug, BuildVersion.Develop, BuildVersion.Review, BuildVersion.Final };
                var versionDefault = BuildVersion.Develop;
                bool isFirst = true;
                foreach (var version in versions)
                {
                    if (!isFirst)
                    {
                        writer.Write(", ");
                    }
                    writer.Write(version.ToString());
                    if (version == versionDefault)
                    {
                        writer.Write("(Default)");
                    }
                    isFirst = false;
                }
                writer.WriteLine("]");
            }
            writer.WriteLine("    -{0}: Project dir path. (Default is current directory.)", nameof(ProjectDir));
            writer.WriteLine("Commands:");
            writer.WriteLine("    Build: Build executable file.");
            writer.WriteLine("    Clean: Clean build files.");
            writer.WriteLine("    Rebuild: Execute build and clean.");
            Console.Error.Write(writer.ToString());
        }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット識別名。
        /// </summary>
        public string BuildTargetUniqueName { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドバージョン。
        /// </summary>
        public BuildVersion BuildVersion { get; set; } = BuildVersion.Develop;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行するコマンド群。
        /// </summary>
        public List<CommandKind> CommandKinds { get; set; } = new List<CommandKind>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクトフォルダパス。
        /// </summary>
        public string ProjectDir { get; set; } = Directory.GetCurrentDirectory();

        //------------------------------------------------------------------------------
        /// <summary>
        /// エンジン開発者用のモードか。
        /// </summary>
        public bool PrivateDevelopMode { get; set; } = false;
    }
}
