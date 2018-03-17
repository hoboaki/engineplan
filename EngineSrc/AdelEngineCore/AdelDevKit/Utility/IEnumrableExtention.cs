using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Utility
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// IEnumerable 拡張メソッド群。
    /// </summary>
    public static class IEnumerableExtension
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// Null なら 空のコレクションをを返す。
        /// </summary>
        public static IEnumerable<T> OrEmptyIfNull<T>(this IEnumerable<T> collection)
        {
            return collection ?? Enumerable.Empty<T>();
        }
    }
}
