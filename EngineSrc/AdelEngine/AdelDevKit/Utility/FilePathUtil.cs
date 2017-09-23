using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Utility
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ファイル・フォルダパスに関する便利関数群。
    /// </summary>
    public static class FilePathUtil
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// Unix パス（フォルダ区切りが '\' ではなく '/'）に変換する。
        /// </summary>
        /// <remarks>元々 Unix パスだった場合は何もしない。</remarks>
        public static string ToUnixPath(string aPath)
        {
            return aPath.Replace(@"\", @"/");
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Dos パス（フォルダ区切りが '/' ではなく '\'）に変換する。
        /// </summary>
        /// <remarks>元々 Dos パスだった場合は何もしない。</remarks>
        public static string ToDosPath(string aPath)
        {
            return aPath.Replace(@"/", @"\");
        }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// Dos パス形式の相対パスに変換する。
        /// </summary>
        public static string ToRelativeDosPath(DirectoryInfo aBaseDir, string aDstPath)
        {
            Uri baseUri = new Uri(aBaseDir.FullName + @"\");
            Uri dstUri = new Uri(aDstPath);
            Uri resultUri = baseUri.MakeRelativeUri(dstUri);
            return resultUri.ToString().Replace(@"/", @"\");
        }
    }
}
