using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdelDevKit.CoreLib
{
    //------------------------------------------------------------------------------
    /// <summary>
    /// CoreLib を扱うクラス。
    /// </summary>
    public class CoreLibManager
    {
        //------------------------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        internal CoreLibManager()
        {
        }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロード済か。
        /// </summary>
        internal bool IsLoaded { get; private set; } = false;

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreOs 群。
        /// </summary>
        internal PluginSystem.AddonInfo<ICoreOsAddon>[] CoreOsAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreGfx 群。
        /// </summary>
        internal PluginSystem.AddonInfo<ICoreGfxAddon>[] CoreGfxAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// ロードされた CoreSnd 群。
        /// </summary>
        internal PluginSystem.AddonInfo<ICoreSndAddon>[] CoreSndAddons { get; private set; }

        //------------------------------------------------------------------------------
        /// <summary>
        /// 各 CoreLib を生成する。
        /// </summary>
        internal void Load(
            CommandLog.Logger aLog,
            PluginSystem.PluginManager aPluginManager
            )
        {
            // チェック
            System.Diagnostics.Debug.Assert(aPluginManager.IsLoaded);

            // アドオン収集
            CoreOsAddons = aPluginManager.Addons.Where(x => x.Addon is ICoreOsAddon).Select(x => x.ConvertTo<ICoreOsAddon>()).ToArray();
            CoreGfxAddons = aPluginManager.Addons.Where(x => x.Addon is ICoreGfxAddon).Select(x => x.ConvertTo<ICoreGfxAddon>()).ToArray();
            CoreSndAddons = aPluginManager.Addons.Where(x => x.Addon is ICoreSndAddon).Select(x => x.ConvertTo<ICoreSndAddon>()).ToArray();

            // 重複チェック
            Utility.ErrorCheckUtil.CheckExistSamePropertyEntry(
                CoreOsAddons,
                (a, b) => { return a.Addon.Name == b.Addon.Name; },
                (items) =>
                {
                    aLog.Error.WriteLine(string.Format("'{0}'という名前の CoreOs アドオンが複数定義されています。({1}個)", items[0].Addon.Name, items.Length));
                    foreach (var item in items)
                    {
                        aLog.Warn.WriteLine("型名'{0}' ファイル'{1}", item.Addon.GetType().FullName, item.PluginInfo.FileInfo.FullName);
                    }
                }
                );
            Utility.ErrorCheckUtil.CheckExistSamePropertyEntry(
                CoreGfxAddons,
                (a, b) => { return a.Addon.Name == b.Addon.Name; },
                (items) =>
                {
                    aLog.Error.WriteLine(string.Format("'{0}'という名前の CoreGfx アドオンが複数定義されています。({1}個)", items[0].Addon.Name, items.Length));
                    foreach (var item in items)
                    {
                        aLog.Warn.WriteLine("型名'{0}' ファイル'{1}", item.Addon.GetType().FullName, item.PluginInfo.FileInfo.FullName);
                    }
                }
                );
            Utility.ErrorCheckUtil.CheckExistSamePropertyEntry(
                CoreSndAddons,
                (a, b) => { return a.Addon.Name == b.Addon.Name; },
                (items) =>
                {
                    aLog.Error.WriteLine(string.Format("'{0}'という名前の CoreSnd アドオンが複数定義されています。({1}個)", items[0].Addon.Name, items.Length));
                    foreach (var item in items)
                    {
                        aLog.Warn.WriteLine("型名'{0}' ファイル'{1}", item.Addon.GetType().FullName, item.PluginInfo.FileInfo.FullName);
                    }
                }
                );
        }
    }
}
