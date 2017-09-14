using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 開発キットのあらゆるオブジェクトへのアクセスを提供するクラス。
    /// </summary>
    public class DevKit
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal DevKit()
        {
            BuildManager = new BuildSystem.BuildManager();
            PluginManager = new PluginSystem.PluginManager();
            TaskManager = new TaskSystem.TaskManager();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドマネージャ。
        /// </summary>
        public BuildSystem.BuildManager BuildManager { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラグインマネージャ。
        /// </summary>
        public PluginSystem.PluginManager PluginManager { get; private set; }
        
        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクマネージャ。
        /// </summary>
        public TaskSystem.TaskManager TaskManager { get; private set; }
    }
}
