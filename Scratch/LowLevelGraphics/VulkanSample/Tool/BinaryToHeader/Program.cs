using System;
using System.IO;
using System.Text;

namespace BinaryToHeader
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (var arg in args)
            {
                var fileInfo = new FileInfo(arg);
                var bytes = File.ReadAllBytes(fileInfo.FullName);
                var dirName = fileInfo.Directory.Name;
                var baseName = Path.GetFileNameWithoutExtension(arg);
                var outputPath = $@"{fileInfo.Directory.FullName}\{baseName}.hpp";

                var builder = new StringBuilder();
                builder.AppendLine($@"namespace {dirName} {{");
                builder.AppendLine($@"constexpr uint8_t {baseName}_Bytes[] = {{");
                string line = "";
                for (int bytesIdx = 0; bytesIdx < bytes.Length; ++bytesIdx)
                {
                    if (line == "")
                    {
                        line += "   ";
                    }
                    line += $" 0x{bytes[bytesIdx].ToString("x2")},";
                    if (120 < line.Length)
                    {
                        builder.AppendLine(line);
                        line = "";
                    }
                }
                if (line != "")
                {
                    builder.AppendLine(line);
                }
                builder.AppendLine($@"}};");
                builder.AppendLine($@"}} // namespace {dirName}");

                File.WriteAllText(outputPath, builder.ToString());
            }
        }
    }
}
