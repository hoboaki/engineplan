using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdelCommandMain
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello AdelCommand. {0}", Assembly.GetExecutingAssembly().Location);
        }
    }
}
