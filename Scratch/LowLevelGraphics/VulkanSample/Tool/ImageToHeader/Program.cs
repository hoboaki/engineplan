using System;
using System.Drawing;
using System.IO;
using System.Text;

namespace ImageToHeader
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (var arg in args)
            {
                var fileInfo = new FileInfo(arg);
                var image = new Bitmap(Image.FromFile(fileInfo.FullName));
                var dirName = fileInfo.Directory.Name;
                var baseName = Path.GetFileNameWithoutExtension(arg);
                var outputPath = $@"{fileInfo.Directory.FullName}\{baseName}.hpp";

                var builder = new StringBuilder();
                builder.AppendLine($@"namespace {dirName} {{");
                builder.AppendLine($@"constexpr int {baseName}_Width = {image.Width};");
                builder.AppendLine($@"constexpr int {baseName}_Height = {image.Width};");
                builder.AppendLine($@"constexpr uint8_t {baseName}_Pixels[] = {{");
                string line = "";
                for (int pixelIdx = 0; pixelIdx < image.Width * image.Height; ++pixelIdx)
                {
                    int x = pixelIdx % image.Width;
                    int y = pixelIdx / image.Width;
                    var color = image.GetPixel(x, y);
                    if (line == "")
                    {
                        line += "   ";
                    }
                    line += $" 0x{color.R.ToString("x2")}, 0x{color.G.ToString("x2")}, 0x{color.B.ToString("x2")},";
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
