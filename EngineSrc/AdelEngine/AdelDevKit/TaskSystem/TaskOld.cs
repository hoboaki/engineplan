using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// １つの処理セットを扱うクラス。
    /// </summary>
    public class TaskOld
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// １つのコマンドを実行するタスクとして作成。
        /// </summary>
        static public TaskOld CreateSingle(Task aCommand, TaskCreateInfo aCreateInfo)
        {
            var obj = new TaskOld();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.Single;
            obj._TaskCommand = aCommand;
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 複数のタスク項目を順次実行するタスクとして作成。
        /// </summary>
        static public TaskOld CreateMultiSerial(IEnumerable<TaskOld> aChildTasks, TaskCreateInfo aCreateInfo)
        {
            var obj = new TaskOld();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.MultiSerial;
            obj._ChildTasks = aChildTasks.ToArray();
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 複数のタスク項目を並列実行するタスクとして作成。
        /// </summary>
        static public TaskOld CreateMultiParallel(IEnumerable<TaskOld> aChildTasks, TaskCreateInfo aCreateInfo)
        {
            var obj = new TaskOld();
            obj.CreateInfo = aCreateInfo;
            obj.Kind = TaskKind.MultiParallel;
            obj._ChildTasks = aChildTasks.ToArray();
            return obj;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 作成時に渡した情報。
        /// </summary>
        public TaskCreateInfo CreateInfo { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの種類。
        /// </summary>
        public TaskKind Kind { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// CreateSingle で指定したコマンド。
        /// </summary>
        public Task TaskCommand
        {
            get
            {
                switch (Kind)
                {
                    case TaskKind.Single:
                        return _TaskCommand;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
        Task _TaskCommand = null;

        //------------------------------------------------------------------------------
        /// <summary>
        /// CreateMultiSingle CreateMultiParallel で指定した子タスク。
        /// </summary>
        public TaskOld[] ChildTasks
        {
            get
            {
                switch (Kind)
                {
                    case TaskKind.MultiSerial:
                    case TaskKind.MultiParallel:
                        return _ChildTasks;

                    default:
                        throw new InvalidOperationException();
                }
            }
        }
        TaskOld[] _ChildTasks = null;
    }
}
