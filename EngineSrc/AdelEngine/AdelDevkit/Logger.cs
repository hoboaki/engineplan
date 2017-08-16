using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk
{
    /// <summary>
    /// ログ出力を扱うクラス。
    /// </summary>
    public class Logger
    {
        /// <summary>
        /// ログメッセージの種類。
        /// </summary>
        public enum MsgKind
        {
            Debug,
            Info,
            Warn,
            Error,
        }

        /// <summary>
        /// ログメッセージを出力する。
        /// </summary>
        /// <param name="aText"></param>
        /// <param name="aKind"></param>
        public void Write(string aText, MsgKind aKind)
        {
            throw new NotImplementedException();
        }
    }
}
