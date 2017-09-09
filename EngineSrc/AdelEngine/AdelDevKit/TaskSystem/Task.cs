using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.TaskSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// タスク。
    /// </summary>
    /// <remarks>
    /// ◆ 概要
    /// 1連のオフライン処理（非ランタイム上の処理）を表すクラスです。
    /// 実行ファイルのビルド、アセットのビルド、SCM 処理といった一瞬で終了しない処理はタスクとして処理されます。
    /// 
    /// ◆ 並列処理について
    /// 開発キットはできる限り多数のタスクを同時に処理します。
    /// 
    /// １つのタスクはエラーが起きない限り中断されることはありません。
    /// 
    /// 例えば１つのタスク内で並列に実行したい処理がある場合は、
    /// タスクの引数に渡される <see cref="TaskExecArg.ExecChildTaskAsync(Task)"/> を使い、
    /// 子タスクとして処理を分割してください。
    /// C# 標準機能である parallel はできる限り使わないようにしてください。
    /// 
    /// 子タスクの分割を推奨しているのは、タスクの同時実行数などを開発キット側がコントロールできるようにするためです。
    /// タスクの同時実行数を開発キット側がコントロールできるようにする恩恵として、
    /// アプリケーションのテストプレイの動作パフォーマンスの影響を最低限にしつつ
    /// できる限りタスクを実行する、というようなことが実現できます。
    /// </remarks>
    public class Task
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// タスクの作成。
        /// </summary>
        public Task(TaskCreateInfo aCreateInfo)
        {
            CreateInfo = aCreateInfo;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 作成情報。
        /// </summary>
        public TaskCreateInfo CreateInfo { get; private set; }
    }
}
