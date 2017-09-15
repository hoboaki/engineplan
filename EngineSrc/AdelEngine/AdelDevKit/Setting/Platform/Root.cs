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
        /// コードネーム。（英小文字・ハイフンで構成）
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
        /// ビルドターゲットの定義。
        /// </summary>
        [JsonProperty()]
        public BuildTarget[] BuildTargets { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// Coreライブラリの設定。（null許容）
        /// </summary>
        [JsonProperty()]
        public CoreLib CoreLib { get; internal set; }

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
            checkFunc(BuildTargets, nameof(BuildTargets));
            foreach (var buildTarget in BuildTargets)
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
