using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Utility
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// エラーチェックに関する便利関数群。
    /// </summary>
    public static class ErrorCheckUtil
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// チェック結果。
        /// </summary>
        public enum CheckResult
        {
            /// <summary>
            /// エラー無しで通過。
            /// </summary>
            NoError,

            /// <summary>
            /// エラー発生。
            /// </summary>
            Error,
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 同じプロパティが存在するかチェックする関数。
        /// </summary>
        /// <param name="aCollection">エラーチェック対象となるコレクション。</param>
        /// <param name="aSameCheckFunc">エラー判定関数。</param>
        /// <param name="aOnErrorFunc">エラー時の関数。</param>
        /// <returns></returns>
        public static CheckResult CheckExistSamePropertyEntry<TType>(
            IEnumerable<TType> aCollection, 
            Func<TType, TType, bool> aSameCheckFunc,
            Action<TType[]> aOnErrorFunc
            )
        {
            foreach (var item in aCollection)
            {
                var items = aCollection.Where(x => aSameCheckFunc(item, x)).ToArray();
                if (1 < items.Length)
                {
                    aOnErrorFunc(items);
                    return CheckResult.Error;
                }
            }
            return CheckResult.NoError;
        }
    }
}
