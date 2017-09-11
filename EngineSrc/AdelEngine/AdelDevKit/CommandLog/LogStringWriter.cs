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
        internal LogStringWriter(LogStringWriteCallback aCallback)
            : base()
        {
            _Callback = aCallback;
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

        //------------------------------------------------------------------------------
        #region 実装の上書き
        public override void Write(char value)
        {
            _Callback.Write(value);
            base.Write(value);
        }
        public override void Write(string value)
        {
            _Callback.Write(value);
            base.Write(value);
        }
        public override void Write(char[] buffer, int index, int count)
        {
            _Callback.Write(buffer, index, count);
            base.Write(buffer, index, count);
        }
        public override Task WriteAsync(char value)
        {
            _Callback.Write(value);
            return base.WriteAsync(value);
        }
        public override Task WriteAsync(string value)
        {
            _Callback.Write(value);
            return base.WriteAsync(value);
        }
        public override Task WriteAsync(char[] buffer, int index, int count)
        {
            _Callback.Write(buffer, index, count);
            return base.WriteAsync(buffer, index, count);
        }
        public override Task WriteLineAsync(char value)
        {
            _Callback.Write(value.ToString() + NewLine);
            return base.WriteLineAsync(value);
        }
        public override Task WriteLineAsync(string value)
        {
            _Callback.Write(value + NewLine);
            return base.WriteLineAsync(value);
        }
        public override Task WriteLineAsync(char[] buffer, int index, int count)
        {
            _Callback.Write(new string(buffer, index, count) + NewLine);
            return base.WriteLineAsync(buffer, index, count);
        }
        #endregion

        //------------------------------------------------------------------------------
        LogStringWriteCallback _Callback;
    }
}
