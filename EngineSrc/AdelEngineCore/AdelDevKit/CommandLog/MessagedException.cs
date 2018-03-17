using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 既に Logger にエラーメッセージを書き込み済の状態で投げられる例外。
    /// </summary>
    /// <remarks>
    /// 例外メッセージを二重に Logger に書き込まないようにするための例外クラス。
    /// </remarks>
    public class MessagedException : Exception
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// デフォルトコンストラクタ。
        /// </summary>
        public MessagedException()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// InnnerException 付きコンストラクタ。
        /// </summary>
        public MessagedException(Exception aExp)
            : base("", aExp)
        {
        }
    }
}
