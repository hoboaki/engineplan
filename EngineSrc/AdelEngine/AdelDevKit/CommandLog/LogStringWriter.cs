using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ログ用文字列書き込みクラス。
    /// </summary>
    public class LogStringWriter : StringWriter
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。（StringBuilderは内部で自動生成したものを使用する）
        /// </summary>
        public LogStringWriter()
            : base()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 文字コードは UTF8 で固定。
        /// </summary>
        public override Encoding Encoding { get { return Encoding.UTF8; } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 改行コードを固定。
        /// </summary>
        public override string NewLine
        {
            get
            {
                return Environment.NewLine;
            }

            set
            {
                // 書き換え不可
            }
        }
    }
}
