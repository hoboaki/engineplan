using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.Setting.Platform
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// プラットフォーム設定のルート。
    /// </summary>
    public class Root
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コードネーム。（パスカル英字・ハイフンで構成）
        /// </summary>
        [JsonProperty()]
        public string Name { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// GUI上などで表示される名前。（分かりやすさ優先）
        /// </summary>
        [JsonProperty()]
        public string DisplayName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// デフォルトビルドターゲットの名前。
        /// </summary>
        [JsonProperty()]
        public string DefaultBuildTargetName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// デフォルトのビルドターゲット設定。（null許容）
        /// </summary>
        [JsonProperty()]
        public BuildTarget DefaultBuildTargetSetting { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット設定群。
        /// </summary>
        [JsonProperty()]
        public BuildTarget[] BuildTargetSettings { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 各ビルドターゲット設定にデフォルトのビルドターゲット設定を適用。
        /// </summary>
        public void ResolveBuildTargetSettings()
        {
            if (DefaultBuildTargetSetting == null)
            {
                return;
            }
            foreach (var buildTarget in BuildTargetSettings)
            {
                buildTarget.MergeDefaultSetting(DefaultBuildTargetSetting);
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 設定に不正があったら例外を投げる。
        /// </summary>
        /// <exception cref="InvalidSettingException"/>
        public void Verify(FileInfo aSrcFile, CommandLog.Logger aLog)
        {
            bool isInvalid = false;
            Action<object, string> checkFunc = (aObject, aVariableName) =>
            {
                if (aObject == null)
                {
                    aLog.Error.WriteLine(string.Format("設定ファイル'{0}'の PlatformSetting パラメータ'{1}'が見つかりません。", aSrcFile.FullName, aVariableName));
                    isInvalid = false;
                }
            };
            checkFunc(Name, nameof(Name));
            checkFunc(DisplayName, nameof(DisplayName));
            checkFunc(DefaultBuildTargetName, nameof(DefaultBuildTargetName));
            checkFunc(BuildTargetSettings, nameof(BuildTargetSettings));
            foreach (var buildTarget in BuildTargetSettings)
            {
                buildTarget.Verify(aSrcFile, aLog);
            }
            if (isInvalid)
            {
                throw new InvalidSettingException();
            }
        }
    }
}
