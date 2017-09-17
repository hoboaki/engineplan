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
        /// 同じプロパティが存在するかチェックする関数。
        /// </summary>
        /// <param name="aCollection">エラーチェック対象となるコレクション。</param>
        /// <param name="aSameCheckFunc">エラー判定関数。</param>
        /// <param name="aOnErrorFunc">エラー時の関数。</param>
        /// <exception cref="CommandLog.MessagedException">エラーが発生したら投げられる。</exception>
        public static void CheckExistSamePropertyEntry<TType>(
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
                    throw new CommandLog.MessagedException();
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 条件に合うものを探しつつ無ければエラー出力する関数。
        /// </summary>
        /// <param name="aCollection">エラーチェック対象となるコレクション。</param>
        /// <param name="aSameCheckFunc">エラー判定関数。</param>
        /// <param name="aOnErrorFunc">エラー時の関数。</param>
        /// <exception cref="CommandLog.MessagedException">エラーが発生したら投げられる。</exception>
        public static TType GetUniqueItem<TType>(
            IEnumerable<TType> aCollection,
            Func<TType, bool> aCheckFunc,
            Action aOnErrorFunc
            )
        {
            var items = aCollection.Where(x => aCheckFunc(x)).ToArray();
            if (items.Length == 0)
            {
                aOnErrorFunc();
                throw new CommandLog.MessagedException();
            }
            System.Diagnostics.Debug.Assert(items.Length == 1); // 2つ以上のものはこの関数で指定してない前提
            return items[0];
        }
    }
}
