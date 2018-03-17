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
    /// UTF-8 固定のStringWriter。
    /// </summary>
    public class Utf8StringWriter : StringWriter
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public Utf8StringWriter()
        {
            // 改行コードのデフォルトはCRLF
            NewLine = "\r\n";
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 文字コードは UTF8 で固定。
        /// </summary>
        public override Encoding Encoding { get { return Encoding.UTF8; } }
    }
}
