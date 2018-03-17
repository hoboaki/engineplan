using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ログの1回の書き込みに関する情報の集合体。
    /// </summary>
    public class LogPacket
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public LogPacket(LogKind aKind, string aText)
        {
            Kind = aKind;
            Text = aText;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログの種類。
        /// </summary>
        public LogKind Kind { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 書き込まれたテキスト。
        /// </summary>
        public string Text { get; private set; }
    }
}
