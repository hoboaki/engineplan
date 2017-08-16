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
    public class TaskCommandCtrl : Livet.NotificationObject
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        public TaskCommandCtrl(TaskCommand aCommand)
        {
            Command = aCommand;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 対象となるコマンド。
        /// </summary>
        public TaskCommand Command { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 状態。
        /// </summary>
        public TaskNodeState State
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
        TaskNodeState _State = TaskNodeState.Wait;

        //------------------------------------------------------------------------------
        /// <summary>
        /// 実行準備状態にする。
        /// </summary>
        public void Prepare()
        {
            if (_State == TaskNodeState.Wait)
            {
                State = TaskNodeState.Prepared;
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
                case TaskNodeState.Wait:
                case TaskNodeState.Prepared:
                    State = TaskNodeState.Canceled;
                    break;
            }
        }
    }
}
