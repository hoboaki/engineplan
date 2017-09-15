﻿using Newtonsoft.Json;
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
    /// ビルドターゲット設定。
    /// </summary>
    public class BuildTarget
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コードネーム。（ロムファイル名に使用）
        /// </summary>
        [JsonProperty()]
        public string Name { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 表示名。分かりやすさ優先。
        /// </summary>
        [JsonProperty()]
        public string DisplayName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用するビルダーの名前。
        /// </summary>
        [JsonProperty()]
        public string BuilderName { get; internal set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーに通知するパラメータ群。
        /// </summary>
        [JsonProperty()]
        public IReadOnlyDictionary<string, object> BuilderParams { get; internal set; } = new Dictionary<string, object>();

        //------------------------------------------------------------------------------
        /// <summary>
        /// コンパイルパラメータ群。
        /// </summary>
        [JsonProperty()]
        public string[] CompileParams { get; internal set; } = new string[0];

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
                    aLog.Error.WriteLine(string.Format("設定ファイル'{0}'の PlatformSetting.BuildTarget パラメータ'{1}'が見つかりません。", aSrcFile.FullName, aVariableName));
                    isInvalid = false;
                }
            };
            Action<object, string> checkFuncWithName = (aObject, aVariableName) =>
            {
                if (aObject == null)
                {
                    aLog.Error.WriteLine(string.Format("設定ファイル'{0}'の PlatformSetting.BuildTarget[name='{1}'] パラメータ'{2}'が見つかりません。", aSrcFile.FullName, Name, aVariableName));
                    isInvalid = false;
                }
            };
            checkFunc(Name, nameof(Name));
            checkFuncWithName(DisplayName, nameof(DisplayName));
            checkFuncWithName(BuilderName, nameof(BuilderName));
            if (isInvalid)
            {
                throw new InvalidSettingException();
            }
        }
    }
}
