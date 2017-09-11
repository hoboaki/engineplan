using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdelDevKit.CommandLog;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog.Tests
{
    [TestClass()]
    public class LoggerTests
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// バリエーションのテスト。
        /// </summary>
        [TestMethod()]
        public void WriteVariationTest()
        {
            {
                var l = new Logger();
                l.Debug.Write(1);
                Assert.AreEqual("1", l.GetText(LogKind.Debug));
                Assert.AreEqual("1", l.Text);
            }
            {
                var l = new Logger();
                l.Debug.Write(true);
                Assert.AreEqual("True", l.GetText(LogKind.Debug));
                Assert.AreEqual("True", l.Text);
            }
            {
                var l = new Logger();
                l.Debug.Write(1.234);
                Assert.AreEqual("1.234", l.GetText(LogKind.Debug));
                Assert.AreEqual("1.234", l.Text);
            }
            {
                var l = new Logger();
                l.Debug.WriteLine("Hoge");
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.GetText(LogKind.Debug));
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.Text);
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.Packets.ToArray()[0].Text);
            }
            {
                var l = new Logger();
                l.Debug.WriteAsync("Hoge");
                Assert.AreEqual("Hoge", l.GetText(LogKind.Debug));
                Assert.AreEqual("Hoge", l.Text);
                Assert.AreEqual("Hoge", l.Packets.ToArray()[0].Text);
            }
            {
                var l = new Logger();
                l.Debug.WriteLineAsync("Hoge");
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.GetText(LogKind.Debug));
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.Text);
                Assert.AreEqual("Hoge" + l.Debug.NewLine, l.Packets.ToArray()[0].Text);
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// GetWriter() テスト。
        /// </summary>
        [TestMethod()]
        public void GetWriterTest()
        {
            var logger = new Logger();
            Assert.AreEqual(logger.Debug, logger.GetWriter(LogKind.Debug));
            Assert.AreEqual(logger.Info, logger.GetWriter(LogKind.Info));
            Assert.AreEqual(logger.Warn, logger.GetWriter(LogKind.Warn));
            Assert.AreEqual(logger.Error, logger.GetWriter(LogKind.Error));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// GetText() テスト。
        /// </summary>
        [TestMethod()]
        public void GetTextTest()
        {
            var l = new Logger();
            l.Debug.Write(1);
            l.Info.Write(2);
            l.Warn.Write(3);
            l.Error.Write(4);
            Assert.AreEqual("1", l.GetText(LogKind.Debug));
            Assert.AreEqual("2", l.GetText(LogKind.Info));
            Assert.AreEqual("3", l.GetText(LogKind.Warn));
            Assert.AreEqual("4", l.GetText(LogKind.Error));
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 結合テキストのテスト。
        /// </summary>
        [TestMethod()]
        public void TextTest()
        {
            var l = new Logger();
            l.Debug.Write(1);
            l.Info.Write(2);
            l.Warn.Write(3);
            l.Error.Write(4);
            Assert.AreEqual("1234", l.Text);
            string str = "";
            foreach(var packet in l.Packets) { str = packet.Text; }
            Assert.AreEqual("1234", l.Text);
        }
    }
}