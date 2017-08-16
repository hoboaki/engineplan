using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクコマンドを制御する内部処理用クラス。
    /// </summary>
    public class CommandCtrl : Livet.NotificationObject
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public CommandCtrl(Command aCommand)
        {
            Command = aCommand;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 対象となるコマンド。
        /// </summary>
        public Command Command { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 状態。
        /// </summary>
        public TaskState State
        {
            get
            {
                return _State;
            }
            set
            {
                if (_State != value)
                {
                    _State = value;
                    RaisePropertyChanged(nameof(State));
                }
            }

        }
        TaskState _State = TaskState.Wait;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行準備状態にする。
        /// </summary>
        public void Prepare()
        {
            if (_State == TaskState.Wait)
            {
                State = TaskState.Prepared;
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行をキャンセルする。
        /// </summary>
        public void Cancel()
        {
            switch (State)
            {
                case TaskState.Wait:
                case TaskState.Prepared:
                    State = TaskState.Canceled;
                    break;
            }
        }
    }
}
