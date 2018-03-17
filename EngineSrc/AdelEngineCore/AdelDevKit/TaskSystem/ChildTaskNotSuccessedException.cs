using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 子タスクが成功しなかったときに投げられる例外。
    /// </summary>
    class ChildTaskNotSuccessedException : Exception
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public ChildTaskNotSuccessedException(bool aExistsCanceled, bool aExistsFailed)
            : base(CreateMessage(aExistsCanceled, aExistsFailed))
        {
            ExistsCancled = aExistsCanceled;
            ExistsFailed = aExistsFailed;
        }
        static string CreateMessage(bool aExistsCanceled, bool aExistsFailed)
        {
            if (aExistsCanceled && aExistsFailed)
            {
                return "子タスクが失敗もしくはキャンセルされました。";
            }
            if (aExistsCanceled && !aExistsFailed)
            {
                return "子タスクがキャンセルされました。";
            }
            if (!aExistsCanceled && aExistsFailed)
            {
                return "子タスクが失敗しました。";
            }
            throw new ArgumentException();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// キャンセルされた子タスクが存在したか。
        /// </summary>
        public bool ExistsCancled { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 失敗した子タスクが存在したか。
        /// </summary>
        public bool ExistsFailed { get; private set; }
    }
}
