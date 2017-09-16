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
            Builder[] aBuilders
            )
        {
            PlatformSetting = aPlatformSetting;
            BuildTargetSetting = aBuildTargetSetting;

            {// ビルダー検索
                var builders = aBuilders.Where(x => x.Addon.Name == BuildTargetSetting.BuilderName).ToArray();
                if (builders.Length == 0)
                {
                    aLog.Error.WriteLine("ビルドターゲット'{0}'で指定しているビルダー'{1}'が見つかりませんでした。", UniqueName, BuildTargetSetting.BuilderName);
                    throw new Exception();
                }
                System.Diagnostics.Debug.Assert(builders.Length == 1); // SettingManager＆BuildManagerレベルで2個以上見つかることはないはず。
                Builder = builders[0];
            }
            {// CoreOs検索

            }
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
        CoreLib.ICoreOsAddon CoreOs { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreGfx。
        /// </summary>
        CoreLib.ICoreGfxAddon CoreGfx { get; set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 使用する CoreSnd。
        /// </summary>
        CoreLib.ICoreGfxAddon CoreSnd { get; set; }
    }
}
