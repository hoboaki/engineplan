using AdelDevKit.Utility;
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
    public class LogStringWriter : Utf8StringWriter
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
        #endregion

        //------------------------------------------------------------------------------
        LogStringWriteCallback _Callback;
    }
}
