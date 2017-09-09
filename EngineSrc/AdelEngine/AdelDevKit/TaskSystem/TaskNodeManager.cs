using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスクノードを管理するクラス。
    /// </summary>
    class TaskNodeManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aCategory">管理対象となるカテゴリ。</param>
        public TaskNodeManager(TaskCategory aCategory)
        {
            Category = aCategory;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 管理対象となるカテゴリ。
        /// </summary>
        public TaskCategory Category { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ノードの追加。
        /// </summary>
        public void Add(TaskNode aNode)
        {
            if (aNode.Category != Category)
            {
                throw new ArgumentException("渡されたノードのカテゴリが不一致です。", nameof(aNode));
            }
            if (aNode.State != TaskState.Prepared)
            {
                throw new ArgumentException("処理済みのノードが渡されました。", nameof(aNode));
            }

            // イベント追加
            aNode.PropertyChanged += Node_PropertyChanged;

            // Prepared リストに追加
            lock (this)
            {
                // Depth値は大きいものが優先。
                // 同じDepth値の場合は末尾に挿入。
                int index = _PreparedTaskNodes.Where(x => x.TaskDepth >= aNode.TaskDepth).Count();
                _PreparedTaskNodes.Insert(index, aNode);
            }
        }
        void Node_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(TaskNode.State))
            {
                // リストの追加削除を行う
                var node = (TaskNode)sender;
                switch (node.State)
                {
                    case TaskState.Canceled:
                    case TaskState.Successed:
                    case TaskState.Failed:
                        {
                            lock (this)
                            {
                                _PreparedTaskNodes.Remove(node);
                                _ExecutedTaskNodes.Remove(node);
                                _FinishedTaskNodes.Add(node);
                            }
                            break;
                        }
                    default:
                        break;
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ルートノードを全てキャンセルする。
        /// </summary>
        public void CancelRootNodeAll()
        {
            lock (this)
            {
                foreach (var node in _PreparedTaskNodes.Where(x => x.TaskDepth == 0).ToArray())
                {
                    node.Cancel();
                }
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 未処理なタスクを取得する。
        /// </summary>
        /// <returns>ない場合は null を返す。</returns>
        public TaskNode PullNextTask()
        {
            TaskNode result = null;
            lock (this)
            {
                if (0 < _PreparedTaskNodes.Count)
                {
                    // 先頭から処理
                    result = _PreparedTaskNodes[0];
                    _PreparedTaskNodes.RemoveAt(0);
                    _ExecutedTaskNodes.Add(result);
                }
            }
            return result;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 全てのタスクが終了しているか取得する。
        /// </summary>
        public bool CheckIsAllTaskFinished()
        {
            lock (this)
            {
                return _PreparedTaskNodes.Count == 0 && _ExecutedTaskNodes.Count == 0;
            }
        }

        //------------------------------------------------------------------------------
        ObservableCollection<TaskNode> _PreparedTaskNodes = new ObservableCollection<TaskNode>();
        ObservableCollection<TaskNode> _ExecutedTaskNodes = new ObservableCollection<TaskNode>();
        ObservableCollection<TaskNode> _FinishedTaskNodes = new ObservableCollection<TaskNode>();
    }
}
