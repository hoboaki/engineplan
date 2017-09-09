using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 子タスクが失敗したときに投げられる例外。
    /// </summary>
    class ChildTaskFailedException : Exception
    {
    }
}
