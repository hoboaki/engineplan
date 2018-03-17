using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Utility
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// IReadOnlyDictionaryExtention 拡張メソッド群。
    /// </summary>
    public static class IReadOnlyDictionaryExtention
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// IReadOnlyDictionary -> Dictionary 変換。
        /// </summary>
        public static Dictionary<TKey, TValue> ToMutableDictionary<TKey, TValue>(this IReadOnlyDictionary<TKey, TValue> aDict)
        {
            return aDict.ToDictionary(kvp => kvp.Key, kvp => kvp.Value);
        }

    }
}
