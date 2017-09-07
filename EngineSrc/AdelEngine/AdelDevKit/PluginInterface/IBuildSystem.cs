using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.PluginInterface
{
    /// <summary>
    /// ビルドシステムアドオン。
    /// </summary>
    public interface IBuildSystem : IAddon
    {
        /// <summary>
        /// アプリケーションをビルドするタスクを作成する。
        /// </summary>
        IEnumerable<System.Threading.Tasks.Task> CreateBuildTasks();
    }
}
