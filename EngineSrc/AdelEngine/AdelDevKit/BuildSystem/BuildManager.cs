using AdelDevKit.CommandLog;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドシステムの管理クラス。
    /// </summary>
    public class BuildManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal BuildManager()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダー群。
        /// </summary>
        public Builder[] Builders{ get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルドターゲット群。
        /// </summary>
        public BuildTarget[] BuildTargets { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ビルダーを生成する。
        /// </summary>
        internal void Load(
            CommandLog.Logger aLog,
            PluginSystem.PluginManager aPluginManager, 
            Setting.SettingManager aSettingManager, 
            CoreLib.CoreLibManager aCoreLibManager
            )
        {
            // チェック
            System.Diagnostics.Debug.Assert(aPluginManager.IsLoaded);
            System.Diagnostics.Debug.Assert(aSettingManager.IsLoaded);
            System.Diagnostics.Debug.Assert(aCoreLibManager.IsLoaded);

            // 控える
            _SettingManager = aSettingManager;

            // ビルダーアドオンを収集
            var addons = aPluginManager.Addons.Where(x => x.Addon is IBuilderAddon).Select(x => x.ConvertTo<IBuilderAddon>()).ToArray();

            // 重複チェック
            Utility.ErrorCheckUtil.CheckExistSamePropertyEntry(
                addons,
                (a, b) => { return a.Addon.Name == b.Addon.Name; },
                (items) =>
                {
                    aLog.Error.WriteLine(string.Format("'{0}'という名前の Builder アドオンが複数定義されています。({1}個)", items[0].Addon.Name, items.Length));
                    foreach (var item in items)
                    {
                        aLog.Warn.WriteLine("型名'{0}' ファイル'{1}", item.Addon.GetType().FullName, item.PluginInfo.FileInfo.FullName);
                    }
                }
                );

            // エラーチェック
            foreach (var addon in addons)
            {
                if (addon.Addon.DefaultCoreOs == null)
                {
                    aLog.Error.WriteLine("ビルダー{0} のデフォルト CoreOs が null です。", addon.Addon.Name);
                    throw new CommandLog.MessagedException();
                }
                if (addon.Addon.DefaultCoreGfx == null)
                {
                    aLog.Error.WriteLine("ビルダー{0} のデフォルト CoreGfx が null です。", addon.Addon.Name);
                    throw new CommandLog.MessagedException();
                }
                if (addon.Addon.DefaultCoreSnd == null)
                {
                    aLog.Error.WriteLine("ビルダー{0} のデフォルト CoreSnd が null です。", addon.Addon.Name);
                    throw new CommandLog.MessagedException();
                }
            }

            // ビルダーを生成
            var builders = new List<Builder>();
            foreach (var addon in addons)
            {
                builders.Add(new Builder(addon));
            }
            Builders = builders.ToArray();

            // ビルドターゲットを作成
            var buildTargets = new List<BuildTarget>();
            foreach (var platfomSetting in aSettingManager.PlatformSettings)
            {
                foreach (var buildTargetSetting in platfomSetting.BuildTargetSettings)
                {
                    buildTargets.Add(new BuildSystem.BuildTarget(aLog, platfomSetting, buildTargetSetting, Builders, aCoreLibManager));
                }
            }
            BuildTargets = buildTargets.ToArray();
            System.Diagnostics.Debug.Assert(0 < BuildTargets.Length); // Setting の Verify() の時点で1つ以上あることは保証されているはず。
        }
        Setting.SettingManager _SettingManager;

        //------------------------------------------------------------------------------
        /// <summary>
        /// IDEプロジェクトを作成する。
        /// </summary>
        internal void CreateIdeProjectFile(CommandLog.Logger aLog, BuildTarget aTarget, bool aIsDevelopMode)
        {
            // チェック
            System.Diagnostics.Debug.Assert(aTarget != null);

            // 引数用意
            var coreLibArg = new CoreLib.CreateNativeCodeBuildInfoArg()
            {
                IsDevelopMode = aIsDevelopMode,
            };
            var buildArg = new BuildArg()
            {
                Log = aLog,
                ProjectSetting = _SettingManager.ProjectSetting,
                PlatformSetting = aTarget.PlatformSetting,
                BuildTargetSetting = aTarget.BuildTargetSetting,
                BuilderParamInfo = new BuildSystem.BuilderParamInfo(aTarget.BuildTargetSetting),
                CoreOsBuildInfo = aTarget.CoreOs.Addon.CreateNativeCodeBulidInfo(coreLibArg),
                CoreGfxBuildInfo = aTarget.CoreGfx.Addon.CreateNativeCodeBulidInfo(coreLibArg),
                CoreSndBuildInfo = aTarget.CoreSnd.Addon.CreateNativeCodeBulidInfo(coreLibArg),
                IsDevelopMode = aIsDevelopMode,
            };
            buildArg.CpuBit = aTarget.Builder.Addon.Addon.GetCpuBit(buildArg.BuilderParamInfo);
            buildArg.Endian = aTarget.Builder.Addon.Addon.GetEndian(buildArg.BuilderParamInfo);

            // 作成
            try
            {
                aTarget.Builder.Addon.Addon.CreateIdeProjectFile(buildArg);
            }
            catch(MessagedException exp)
            {
                throw exp;
            }
            catch(Exception exp)
            {
                aLog.Error.WriteLine("IDEプロジェクト作成中にエラーが発生しました。");
                aLog.Warn.WriteLine(exp.ToString());
                throw new MessagedException(exp);
            }
        }

    }
}
