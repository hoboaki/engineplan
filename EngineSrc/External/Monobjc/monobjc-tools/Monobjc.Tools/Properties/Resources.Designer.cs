﻿//------------------------------------------------------------------------------
// <auto-generated>
//     このコードはツールによって生成されました。
//     ランタイム バージョン:4.0.30319.42000
//
//     このファイルへの変更は、以下の状況下で不正な動作の原因になったり、
//     コードが再生成されるときに損失したりします。
// </auto-generated>
//------------------------------------------------------------------------------

namespace Monobjc.Tools.Properties {
    using System;
    
    
    /// <summary>
    ///   ローカライズされた文字列などを検索するための、厳密に型指定されたリソース クラスです。
    /// </summary>
    // このクラスは StronglyTypedResourceBuilder クラスが ResGen
    // または Visual Studio のようなツールを使用して自動生成されました。
    // メンバーを追加または削除するには、.ResX ファイルを編集して、/str オプションと共に
    // ResGen を実行し直すか、または VS プロジェクトをビルドし直します。
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   このクラスで使用されているキャッシュされた ResourceManager インスタンスを返します。
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Monobjc.Tools.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   厳密に型指定されたこのリソース クラスを使用して、すべての検索リソースに対し、
        ///   現在のスレッドの CurrentUICulture プロパティをオーバーライドします。
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Command returned: {0} に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string CommandReturned {
            get {
                return ResourceManager.GetString("CommandReturned", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Found a valid revision : {0} に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string FoundValidRevision {
            get {
                return ResourceManager.GetString("FoundValidRevision", resourceCulture);
            }
        }
        
        /// <summary>
        ///   IB file &apos;{0}&apos; is up-to-date. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string IBFileUpToDate {
            get {
                return ResourceManager.GetString("IBFileUpToDate", resourceCulture);
            }
        }
        
        /// <summary>
        ///   MOMC model &apos;{0}&apos; is up-to-date. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string MomcModelUpToDate {
            get {
                return ResourceManager.GetString("MomcModelUpToDate", resourceCulture);
            }
        }
        
        /// <summary>
        ///   No dictionary found in the command&apos;s result. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string NoDictionaryFound {
            get {
                return ResourceManager.GetString("NoDictionaryFound", resourceCulture);
            }
        }
        
        /// <summary>
        ///   One or more errors occurred during the parsing. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string ParsingError {
            get {
                return ResourceManager.GetString("ParsingError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   One or more errors occurred during the processing. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string ProcessingError {
            get {
                return ResourceManager.GetString("ProcessingError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   {0}: {1} に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string ValueDescriptionFormat {
            get {
                return ResourceManager.GetString("ValueDescriptionFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   The XIB compilation failed. に類似しているローカライズされた文字列を検索します。
        /// </summary>
        internal static string XibCompilationFailed {
            get {
                return ResourceManager.GetString("XibCompilationFailed", resourceCulture);
            }
        }
    }
}