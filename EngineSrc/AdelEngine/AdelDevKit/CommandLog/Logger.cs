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
    /// <remarks>
    /// ◆ マルチスレッドの方針
    /// 各プロパティや関数のアクセスは全てスレッドセーフです。
    /// ただし、各書き込みオブジェクトのマルチスレッド対応は使用側で行ってください。
    /// 例えば、 <see cref="Debug"/> オブジェクトに対して複数のスレッドから
    /// 同時に書き込むことがある場合は <see cref="Debug"/> を lock してください。
    /// </remarks>
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
        /// 全種類のログを出力順に連結したテキスト。
        /// </summary>
        public string Text
        {
            get
            {
                lock (this)
                {
                    return _TextStringBuilder.ToString();
                }
            }
        }
        StringBuilder _TextStringBuilder = new StringBuilder();
        Dictionary<LogKind, LogStringWriter> _Writers = new Dictionary<LogKind, LogStringWriter>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログを出力順に格納したパケット群。
        /// </summary>
        /// <remarks>
        /// 呼び出し時に格納されたパケットを格納した配列を返します。
        /// 呼び出し以降に格納されたパケットが戻り値の配列に積まれることはありません。
        /// 本プロパティはログの種類によって色分けして表示したいときに使うことを想定しています。
        /// </remarks>
        public LogPacket[] Packets
        {
            get
            {
                lock (this)
                {
                    return _Packets.ToArray();
                }
            }
        }
        List<LogPacket> _Packets = new List<LogPacket>();

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
                    lock (this)
                    {
                        _TextStringBuilder.Append(str);
                        _Packets.Add(new LogPacket(aKind, str));
                    }
                };
                _Writers.Add(aKind, new LogStringWriter(new LogStringWriteCallback(callback)));
            }
            return _Writers[aKind];
        }

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
            lock (writer)
            {
                return writer.GetStringBuilder().ToString();
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンソールに内容をダンプする。
        /// </summary>
        public void DumpToConsole()
        {
            foreach(var packet in Packets)
            {
                switch(packet.Kind)
                {
                    case LogKind.Warn:
                    case LogKind.Error:
                        Console.Error.Write(packet.Text);
                        break;

                    default:
                        Console.Write(packet.Text);
                        break;
                }
            }
        }
    }
}
