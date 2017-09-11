using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ログ書き込み時のコールバック。
    /// </summary>
    class LogStringWriteCallback
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ログが書かれたときに呼び出される関数。
        /// </summary>
        public delegate void LogStringWritten(string aText);

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public LogStringWriteCallback(LogStringWritten aLogStringWritten)
        {
            _LogStringWritten = aLogStringWritten;
        }
        LogStringWritten _LogStringWritten;

        //------------------------------------------------------------------------------
        #region LogStringWriter から呼ばれる関数群。
        public void Write(char aValue)
        {
            _LogStringWritten(aValue.ToString());
        }
        public void Write(string aValue)
        {
            _LogStringWritten(aValue);
        }
        public void Write(char[] aBuffer, int aIndex, int aCount)
        {
            _LogStringWritten(new string(aBuffer, aIndex, aCount));
        }
        #endregion

    }
}
