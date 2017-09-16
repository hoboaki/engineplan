﻿using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using YamlDotNet.RepresentationModel;
using YamlDotNet.Serialization;

namespace AdelDevKit.Setting
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// Setting 以下の設定ファイルを読み込みアクセスできるようにするクラス。
    /// </summary>
    /// <remarks>
    /// 本モジュールは静的な設定情報を扱います。
    /// エディタ起動中に変わるような動的な設定情報は <see cref="Config.ConfigManager"/> で扱います。
    /// </remarks>
    public class SettingManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal SettingManager()
            : this(new CommandLog.Logger())
        {
        }
        internal SettingManager(CommandLog.Logger aLog)
        {
            Logger = aLog;
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 設定ファイルを全てロードする。
        /// </summary>
        internal void Load(DirectoryInfo aSettingDir)
        {
            // 存在しなければ何もしない
            if (!aSettingDir.Exists)
            {
                return;
            }

            // ymlファイルを検索
            var projectSettings = new List<KeyValuePair<FileInfo, Project.Root>>();
            var platformSettings = new List<KeyValuePair<FileInfo, Platform.Root>>();
            var yamlDes = new Deserializer();
            var jsonSer = new JsonSerializer();
            foreach (var yamlFileInfo in aSettingDir.EnumerateFiles("*.yml", SearchOption.AllDirectories))
            {
                try
                {
                    // 実装メモ：
                    // 扱いやすいので一度 json.net クラスに変換して処理をしています

                    // Yaml -> Json 変換
                    string jsonText = null;
                    using (var reader = new StreamReader(yamlFileInfo.FullName, Encoding.UTF8))
                    {
                        var yamlObj = yamlDes.Deserialize(reader);
                        var textWriter = new StringWriter();
                        jsonSer.Serialize(textWriter, yamlObj);
                        jsonText = textWriter.ToString();
                    }

                    // ルート要素を取得
                    var jsonObj = JObject.Parse(jsonText);
                    if (jsonObj.Type != JTokenType.Object)
                    {
                        Logger.Error.WriteLine(string.Format("設定ファイル'{0}'のルート要素が Map ではありません。({1})", yamlFileInfo.FullName, jsonObj.Type.ToString()));
                        continue;
                    }

                    // 1つ目の要素を取得
                    var jsonProps = jsonObj.Properties().ToArray();
                    if (jsonProps.Length != 1)
                    {
                        Logger.Error.WriteLine(string.Format("設定ファイル'{0}'のルート要素が１つではありません。({1}個)", yamlFileInfo.FullName, jsonProps.Length));
                        continue;
                    }
                    var jsonHead = jsonProps[0];

                    // 名前で型を判別してデシリアライズ
                    switch (jsonHead.Name)
                    {
                        case "ProjectSetting":
                            {
                                projectSettings.Add(new KeyValuePair<FileInfo, Project.Root>(
                                    yamlFileInfo,
                                    jsonHead.Value.ToObject<Project.Root>()
                                    ));
                                break;
                            }

                        case "PlatformSetting":
                            {
                                var obj = jsonHead.Value.ToObject<Platform.Root>();
                                try
                                {
                                    obj.ResolveBuildTargetSettings();
                                    obj.Verify(yamlFileInfo, Logger);
                                    platformSettings.Add(new KeyValuePair<FileInfo, Platform.Root>(
                                        yamlFileInfo,
                                        obj
                                        ));
                                }
                                catch (InvalidSettingException)
                                {
                                }
                                catch (Exception exp)
                                {
                                    throw exp;
                                }
                                break;
                            }
                    }
                }
                catch (Exception exp)
                {
                    Logger.Error.WriteLine(string.Format("設定ファイル'{0}'の読み込み処理中に不明なエラーが発生しました。", yamlFileInfo.FullName));
                    Logger.Warn.WriteLine(exp.ToString());
                    return;
                }
            }

            // 総数チェック
            if (projectSettings.Count == 0)
            {
                Logger.Error.WriteLine("プロジェクト設定ファイルが見つかりませんでした。");
                return;
            }
            if (1 < projectSettings.Count)
            {
                Logger.Error.WriteLine(string.Format("プロジェクト設定ファイルが複数存在します。({0}個)", projectSettings.Count));
                return;
            }

            // 重複チェック
            foreach (var platformSetting in platformSettings)
            {
                var sameNamePlatformSettings = platformSettings.Where(x => x.Value.Name == platformSetting.Value.Name).ToArray();
                if (1 < sameNamePlatformSettings.Length)
                {
                    Logger.Error.WriteLine(string.Format("'{0}'という名前のプラットフォームが複数定義されています。({1}個)", platformSetting.Value.Name, sameNamePlatformSettings.Length));
                    foreach (var sameNamePlatformSetting in sameNamePlatformSettings)
                    {
                        Logger.Warn.WriteLine(sameNamePlatformSetting.Key.FullName);
                    }
                    return;
                }
            }

            // 保存
            ProjectSetting = projectSettings[0].Value;
            PlatformSettings = platformSettings.Select(x => x.Value).ToArray();
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード処理のログ。
        /// </summary>
        internal CommandLog.Logger Logger { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プロジェクト設定。
        /// </summary>
        public Project.Root ProjectSetting { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// プラットフォーム設定。
        /// </summary>
        public Platform.Root[] PlatformSettings { get; private set; }
    }
}
