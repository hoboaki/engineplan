using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Config
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// 様々な動的設定情報を扱うクラス。
    /// </summary>
    /// <remarks>
    /// 本モジュールは動的な設定情報を扱います。
    /// 起動後以降変更されない静的な設定情報は <see cref="Setting.SettingManager"/> で扱います。
    /// </remarks>
    public class ConfigManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドに関する設定情報。
        /// </summary>
        public Build Build { get; private set; } = new Build();
    }
}
