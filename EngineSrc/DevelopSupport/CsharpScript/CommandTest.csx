// 文字コード：UTF-8
#load "./Command.csx"
Command.Execute("MSBuild", "/version");
Console.WriteLine(Command.Capture("cat", "./CommandTest.csx"));
Console.WriteLine(Command.Capture("which", "MSBuild"));
Command.Exit(0);
// EOF
