using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// コンソールにログの内容をそのまま流すロガー。
    /// </summary>
    public class ConsoleLogger : Logger
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public ConsoleLogger()
        {
            var packets = (INotifyCollectionChanged)this.Packets;
            packets.CollectionChanged += Packets_CollectionChanged;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ログパケットをコンソールに出力。
        /// </summary>
        void Packets_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    foreach (LogPacket item in e.NewItems)
                    {
                        // コンソールカラーの切り替え
                        if (LastLogKind_ == null || item.Kind != LastLogKind_)
                        {
                            // 変わった場合のみ切り替える
                            LastLogKind_ = item.Kind;
                            switch (LastLogKind_)
                            {
                                case LogKind.Debug:
                                    Console.ResetColor();
                                    if (Console.BackgroundColor != ConsoleColor.DarkGray) // 文字が見えなくならないように。
                                    {
                                        Console.ForegroundColor = ConsoleColor.DarkGray;
                                    }
                                    break;

                                case LogKind.Info:
                                    Console.ResetColor();
                                    break;

                                case LogKind.Warn:
                                    Console.ResetColor();
                                    Console.ForegroundColor = ConsoleColor.Yellow;
                                    break;

                                case LogKind.Error:
                                    Console.BackgroundColor = ConsoleColor.Red;
                                    Console.ForegroundColor = ConsoleColor.White;
                                    break;
                            }
                        }

                        // 出力
                        switch (item.Kind)
                        {
                            case LogKind.Warn:
                            case LogKind.Error:
                                Console.Error.Write(item.Text);
                                break;

                            default:
                                Console.Out.Write(item.Text);
                                break;
                        }
                    }
                    break;

                default:
                    throw new NotImplementedException();
            }
        }
        LogKind? LastLogKind_;
    }
}
