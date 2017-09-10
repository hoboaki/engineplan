using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コマンド処理などの出力するログの記録を扱うクラス。
    /// </summary>
    public class Logger
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public Logger()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// デバッグ情報用書き込みオブジェクト。
        /// </summary>
        public LogStringWriter Debug { get { return GetWriter(LogKind.Debug); } }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// 一般情報用ログ書き込みオブジェクト。
        /// </summary>
        public LogStringWriter Info { get { return GetWriter(LogKind.Info); } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 警告情報用ログ書き込みオブジェクト。
        /// </summary>
        public LogStringWriter Warn { get { return GetWriter(LogKind.Warn); } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// エラー情報用ログ書き込みオブジェクト。
        /// </summary>
        public LogStringWriter Error { get { return GetWriter(LogKind.Error); } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 指定の種類のログ書き込みオブジェクトを取得。
        /// </summary>
        public LogStringWriter GetWriter(LogKind aKind)
        {
            if (!_Writers.ContainsKey(aKind))
            {
                LogStringWriteCallback.LogStringWritten callback = (str) =>
                {
                };
                _Writers.Add(aKind, new LogStringWriter(new LogStringWriteCallback(callback)));
            }
            return _Writers[aKind];
        }
        Dictionary<LogKind, LogStringWriter> _Writers = new Dictionary<LogKind, LogStringWriter>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// 指定の種類のログテキストを取得。
        /// </summary>
        /// <returns>書き込まれたテキストがあればその文字列。ない場合は空文字列。</returns>
        public string GetText(LogKind aKind)
        {
            // メモ：
            // なるべくオブジェクトを増やさないように GetWriter() は使わない。
            var writer = _Writers[aKind];
            if (writer == null)
            {
                return "";
            }
            return writer.GetStringBuilder().ToString();
        }
    }
}
