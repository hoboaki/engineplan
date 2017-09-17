using Newtonsoft.Json;
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
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

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

        //------------------------------------------------------------------------------
        /// <summary>
        /// 設定ファイルを全てロードする。
        /// </summary>
        internal void Load(CommandLog.Logger Log, DirectoryInfo aSettingDir)
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
                        Log.Error.WriteLine(string.Format("設定ファイル'{0}'のルート要素が Map ではありません。({1})", yamlFileInfo.FullName, jsonObj.Type.ToString()));
                        throw new CommandLog.MessagedException();
                    }

                    // 1つ目の要素を取得
                    var jsonProps = jsonObj.Properties().ToArray();
                    if (jsonProps.Length != 1)
                    {
                        Log.Error.WriteLine(string.Format("設定ファイル'{0}'のルート要素が１つではありません。({1}個)", yamlFileInfo.FullName, jsonProps.Length));
                        throw new CommandLog.MessagedException();
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
                                    obj.Verify(yamlFileInfo, Log);
                                    platformSettings.Add(new KeyValuePair<FileInfo, Platform.Root>(
                                        yamlFileInfo,
                                        obj
                                        ));
                                }
                                catch (InvalidSettingException)
                                {
                                    throw new CommandLog.MessagedException();
                                }
                                catch (Exception exp)
                                {
                                    throw exp;
                                }
                                break;
                            }
                    }
                }
                catch (CommandLog.MessagedException exp)
                {
                    throw exp;
                }
                catch (Exception exp)
                {
                    Log.Error.WriteLine(string.Format("設定ファイル'{0}'の読み込み処理中に不明なエラーが発生しました。", yamlFileInfo.FullName));
                    Log.Warn.WriteLine(exp.ToString());
                    throw new CommandLog.MessagedException();
                }
            }

            // 総数チェック
            if (projectSettings.Count == 0)
            {
                Log.Error.WriteLine("プロジェクト設定ファイルが見つかりませんでした。");
                throw new CommandLog.MessagedException();
            }
            if (1 < projectSettings.Count)
            {
                Log.Error.WriteLine(string.Format("プロジェクト設定ファイルが複数存在します。({0}個)", projectSettings.Count));
                throw new CommandLog.MessagedException(); ;
            }

            // 重複チェック
            Utility.ErrorCheckUtil.CheckExistSamePropertyEntry(
                platformSettings,
                (a, b) => { return a.Value.Name == b.Value.Name; },
                (items) =>
                {
                    Log.Error.WriteLine(string.Format("'{0}'という名前のプラットフォームが複数定義されています。({1}個)", items[0].Value.Name, items.Length));
                    foreach (var item in items)
                    {
                        Log.Warn.WriteLine(item.Key.FullName);
                    }
                }
                );

            // 保存
            ProjectSetting = projectSettings[0].Value;
            PlatformSettings = platformSettings.Select(x => x.Value).ToArray();
            IsLoaded = true;
        }

    }
}
