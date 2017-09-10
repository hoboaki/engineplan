using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CommandLog
{
    interface ILogStringCallback
    {
        void Write(char aValue);
        void Write(string aValue);
        void Write(char[] aBuffer, int aIndex, int aCount);
    }
}
