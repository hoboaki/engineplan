using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.BuildSystem
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// ビルドターゲット。
    /// </summary>
    public class BuildTarget
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal BuildTarget(
            CommandLog.Logger aLog,
            Setting.Platform.Root aPlatformSetting, 
            Setting.Platform.BuildTarget aBuildTargetSetting, 
            Builder[] aBuilders,
            CoreLib.CoreLibManager aCoreLibManager
            )
        {
            PlatformSetting = aPlatformSetting;
            BuildTargetSetting = aBuildTargetSetting;

            Builder = Utility.ErrorCheckUtil.GetUniqueItem(
                aBuilders,
                (x) => { return x.Addon.Addon.Name == BuildTargetSetting.BuilderName; },
                () =>
                {
                    aLog.Error.WriteLine("ビルドターゲット'{0}'で指定しているビルダー'{1}'が見つかりませんでした。", UniqueName, BuildTargetSetting.BuilderName);
                }
                );
            CoreOs = Utility.ErrorCheckUtil.GetUniqueItem(
                aCoreLibManager.CoreOsAddons,
                (x) => { return x.Addon.Name == CoreOsName; },
                () =>
                {
                    aLog.Error.WriteLine("ビルドターゲット'{0}'で指定している CoreOs'{1}'が見つかりませんでした。", UniqueName, CoreOsName);
                }
                );
            CoreGfx = Utility.ErrorCheckUtil.GetUniqueItem(
                aCoreLibManager.CoreGfxAddons,
                (x) => { return x.Addon.Name == CoreGfxName; },
                () =>
                {
                    aLog.Error.WriteLine("ビルドターゲット'{0}'で指定している CoreSnd'{1}'が見つかりませんでした。", UniqueName, CoreGfxName);
                }
                );
            CoreSnd = Utility.ErrorCheckUtil.GetUniqueItem(
                aCoreLibManager.CoreSndAddons,
                (x) => { return x.Addon.Name == CoreSndName; },
                () =>
                {
                    aLog.Error.WriteLine("ビルドターゲット'{0}'で指定している CoreSnd'{1}'が見つかりませんでした。", UniqueName, CoreSndName);
                }
                );
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ユニーク名。（PlatformName + "/" + BuildTargetName）
        /// </summary>
        public string UniqueName { get { return PlatformSetting.Name + "/" + BuildTargetSetting.Name; } }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 所属するプラットフォーム。
        /// </summary>
        public Setting.Platform.Root PlatformSetting { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 本ビルドターゲットの設定情報。
        /// </summary>
        public Setting.Platform.BuildTarget BuildTargetSetting { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用するビルダー。
        /// </summary>
        internal Builder Builder { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreOs。
        /// </summary>
        PluginSystem.AddonInfo<CoreLib.ICoreOsAddon> CoreOs { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreOs の名前。
        /// </summary>
        string CoreOsName
        {
            get
            {
                var name = BuildTargetSetting.CoreLib?.CoreOs;
                if (name == null)
                {
                    name = Builder.Addon.Addon.DefaultCoreLib.CoreOs;
                }
                return name;
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreGfx。
        /// </summary>
        PluginSystem.AddonInfo<CoreLib.ICoreGfxAddon> CoreGfx { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreGfx の名前。
        /// </summary>
        string CoreGfxName
        {
            get
            {
                var name = BuildTargetSetting.CoreLib?.CoreGfx;
                if (name == null)
                {
                    name = Builder.Addon.Addon.DefaultCoreLib.CoreGfx;
                }
                return name;
            }
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreSnd。
        /// </summary>
        PluginSystem.AddonInfo<CoreLib.ICoreSndAddon> CoreSnd { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreSnd の名前。
        /// </summary>
        string CoreSndName
        {
            get
            {
                var name = BuildTargetSetting.CoreLib?.CoreSnd;
                if (name == null)
                {
                    name = Builder.Addon.Addon.DefaultCoreLib.CoreSnd;
                }
                return name;
            }
        }
    }
}
