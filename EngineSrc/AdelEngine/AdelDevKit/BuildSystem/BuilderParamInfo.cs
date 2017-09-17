using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルダー用パラメータ情報。
    /// </summary>
    /// <remarks><see cref="Setting.Platform.BuildTarget.BuilderParams"/> のエイリアス。</remarks>
    public class BuilderParamInfo
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal BuilderParamInfo(Setting.Platform.BuildTarget aTarget)
        {
            BuildTargetSettingParams = aTarget.BuilderParams;
            if (BuildTargetSettingParams == null)
            {
                BuildTargetSettingParams = new Dictionary<string, object>();
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット設定で指定されたパラメータ群。
        /// </summary>
        public IReadOnlyDictionary<string, object> BuildTargetSettingParams { get; private set; }
    }
}
