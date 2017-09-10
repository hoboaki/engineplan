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
            : base("子タスクが失敗もしくはキャンセルされました。")
        {
            ExistsCancled = aExistsCanceled;
            ExistsFailed = aExistsFailed;
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
