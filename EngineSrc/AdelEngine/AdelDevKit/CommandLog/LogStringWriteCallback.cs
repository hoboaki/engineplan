using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    class LogStringWriteCallback
    {
        public delegate void LogStringWritten(string aText);

        public LogStringWriteCallback(LogStringWritten aLogStringWritten)
        {
            _LogStringWritten = aLogStringWritten;
        }
        LogStringWritten _LogStringWritten;

        public void Write(char aValue)
        {
            _LogStringWritten(aValue.ToString());
        }

        public void Write(string aValue)
        {
            _LogStringWritten(aValue);
        }

        public void Write(char[] aBuffer, int aIndex, int aCount)
        {
            _LogStringWritten(new string(aBuffer, aIndex, aCount));
        }

    }
}
