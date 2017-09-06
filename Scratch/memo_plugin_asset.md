# アセットプラグイン関連メモ

## アセットのバイナリタイプ

- Universal （OS・デバイス非依存）
    - エンディアンだけ変わる。32bit64bitはひとまず64bit固定とする。
    - UniversalLE
    - UniversalBE
- GraphicsResouce（Shader・Texture・VertexAttribute）
    - CoreGfxのタイプによって生成物が変わりそう。
    - WinDx11
    - WinVk
    - WinGl330
    - IosGles300
    - IosMtl
    - MacGl330
    - MacMtl
    
## グラフィックスアセットの検討

- .fbx .dae
    - Ae.Gfx.ResScn
    - Ae.Gfx.ResScnAnimSkl
- .aemat .aematanim MaterialEditor
    - Ae.Gfx.ResMat
    - Ae.Gfx.ResMatAnim
    - Ae.Gfx.ResShd
- .aepfx PosteffectEditor
    - Ae.Gfx.ResPfx Ae.Gfx.ResPfxAnim
- .aevfx VfxEditor
    - Ae.Gfx.ResVfx
- .tga .dds
    - Ae.Gfx.ResTex
- シェーダーリソース
    - Ae.Gfx.ResShader

```c#
Adk.Devkit.ActivePlatform.Gfx.Binarizer.FbxToResMdl()
Adk.Devkit.ActivePlatform.Gfx.Binarizer.TgaToResTex()
Adk.Devkit.ActivePlatform.Gfx.Binarizer.GlslToResShader(env,geom,vert,frag,comp)

// class CoreGfxGl330 : Adk.PluginInterface.ICoreLibGfx
AdkExt.DevkitWin.CoreGfxGl330.Binarizer.GlslToResShader(...)
```

## アセットシステムの検討

- アセットシステムが使うフォルダ
    - $(ProjectRoot)/.Build/Adel.Asset
        - /Hash.db => 各アセットファイル（コンバート前のファイル）のデータハッシュ値DB
        - /$(ランタイムアセットファイルパスのハッシュ値) => 対象アセットのビルドで使える領域
    - $(ProjectRoot)/.Build/$(Plugin) (例：Adel.Fbx)
        - プラグインのワーク領域（どう使うかはプラグインに任される）
    - $(ProjectRoot)/.Cache
        - /Adel.Asset/$(ランタイムアセットファイルパスのハッシュ値)/$(アセット依存情報のハッシュ値).file
- アセットのビルド作業フォルダ＆キャッシュフォルダに関する補足
    - プラットフォーム名やビルドターゲット名はパスには含めなくてよい
        - それらの情報はアセット依存情報のハッシュ値に含まれているから。
    - ファイルパスのハッシュ値は64bit。
        - FAT32でも大丈夫なようにしたいので1フォルダあたり0xFFFF エントリーまで。
        - ファイルパスもその単位で区切るようにする。
        - 例：ファイルパスのハッシュ値が 0x0123456789ABCDEF 、依存情報のハッシュ値が 1010202030304040 の場合
            - /.Cache/Adel.Asset/0123/4567/89AB/CDEF/1010202030304040.file 
        - 依存情報のハッシュ値をファイル名に使うことで上書きが発生しなくなる。（衝突がないことが保証できれば）
            - その結果、ゲームアプリがファイルをリード中でもアセットのビルドができる。
    
- アセットのリビルドの必要性が確認されたら
    - キャッシュサーバーへの問い合わせ
    - ビルド済みバイナリがあった場合
        - キャッシュサーバーからビルド済みのアセットを入手
    - ビルド済みバイナリがなかった場合
        - アセットビルドタスクをつむ
    - 実行ファイルにアセットの新しいバイナリのファイルパスを通知する (.Cache/Adel.Asset 以下のファイルパス)

- キャッシュフォルダについて
    - $(ProjectRoot)/.Cache
    - ここ以下のファイル達はキャッシュサーバーと通信してデータをアップロード＆ダウンロードする。
    - 目的は、同じアセットのビルドを他のPCで行わないようにし、ビルド時間を短縮化させるため。
    - 実行ファイルのビルドのキャッシュもできて良いかもしれないので、アセットビルドに限定しない構成にしておく。

- 登場人物
    - アセット
        - 元データファイル、中間データ、ランタイムファイル、総じてアセットと呼ぶ。
    - アセットタイプ
        - アセットの型。
    - アセットコンバータ
        - アセットを別のアセットに変換する機能。

## グラフィックスのデータフロー例

モデル(GfxMdlBundle)を作る
- モデルはシーン(GfxScnBundle,シーングラフのこと)とシーンが要するマテリアル設定(複数のGfxMatBundle)が必要
- マテリアル設定はシーンによって変わる（各マテリアル設定にどのマテリアルアセットを割り当てるか）
- マテリアルアセットはコンバート時に必要なパラメータが求められる
    - 特定のマテリアルではカラーの指定が求められたり、テクスチャを求められたり。

### 共通クラス

[Class]GfxResRuntimeKey
- uint32_t FileId; // ファイルId
- string EntryName; // エントリー名

### Fbx -> Scn(GfxScnBundle)

[Imd/RtFile]Asset.GfxScnBundle :
- GfxScn scene;
- GfxResRuntimeKey sceneRuntimeKey;

[OrgFile]Asset.FbxFile :

[ConvParam]Converter.FbxFileToGfxScnBundle.AssetSideConvertParam
- GfxConvertPolicy ConvertPolicy; // コンバート方針 [自動, メモリ効率優先, IOアクセス効率優先]

[Conv]Converter.FbxFileToGfxScnBundle.Converter :
- TypeInfo InputAssetType = FbxFile // 入力に使うアセットタイプ
- TypeInfo OutputAssetType = GfxScnBundle // 出力に使うアセットタイプ
- ConvertParam AssetSideConvertParam = Converter.FbxFileToGfxScnBundle.AssetSideConvertParam // アセット側で指定するコンバートパラメータ
- ConvertParam ReferenceSideConvertParam = null // アセット参照側で指定するコンバートパラメータ

### Aemat -> Mat(GfxMatBundle)

[Imd]Asset.GfxMatBundle
- GfxMat material;
- GfxShd[] shaders; // 一緒に出力されたシェーダ
- GfxTex[] textures; // 一緒に出力されたテクスチャ
- GfxResRuntimeKey[] texturesRuntimeKeys; // 一緒に出力されたテクスチャのラインタイムアクセス用キー

[Class]Asset.GfxMatBundleConvertHint // アセット参照側からコンバータに渡すコンバートのヒント
- int SkinningWeightCountMax // スキニングのウェイトの最大数

[OrgFile]Asset.AematFile

[ConvParam]Converter.AematToGfxMatBandle.ReferenceSideConvertParam
- DynamicParams[] dynamicParams; // AematFileの内容によって決まる動的パラメータ

[Conv]Converter.AematToGfxMatBandle.Converter
- TypeInfo InputAssetType = AematFile
- TypeInfo OutputAssetType = GfxMatBundle
- ConvertParam AssetSideConvertParam = null
- ConvertParam ReferenceSideConvertParam = Converter.AematToGfxMatBandle.ReferenceSideConvertParam

[Imd]Asset.GfxTexBundle
- GfxTex texture;
- GfxResRuntimeKey[] textureRuntimeKey;

[OrgFile]Asset.TgaFile

[ConvParam]Converter.TgaFileToGfxTexBundle.AssetSideConvertParam
- GfxConvertPolicy ConvertPolicy;
- GfxTexFormat Format; // [圧縮sRGB, 圧縮Linear, 非圧縮sRGB, 非圧縮Linear]

[Conv]Converter.TgaFileToGfxTexBundle.Converter
- TypeInfo InputAssetType = TgaFile
- TypeInfo OutputAssetType = GfxTexBundle
- ConvertParam AssetSideConvertParam = Converter.TgaFileToGfxTexBundle.AssetSideConvertParam
- ConvertParam ReferenceSideConvertParam = null

### Scn&Mat -> Mdl(GfxMdlBundle)

[OrgFile]Asset.AemdlFile
- AssetRef<GfxScnBundle> scene;
- Dictionary<string, AssetRef<GfxMatBundle>> materials;

[Imd]Asset.GfxMdlBundle
- GfxMdl model;
- GfxRefRuntimeKey modekRuntimeKey;

[Conv]Converter.AemdlFileToGfxMdlBundle.Converter
- TypeInfo InputAssetType = AemdlFile
- TypeInfo OutputAssetType = GfxMdlBundle
- ConvertParam AssetSideConvertParam = null
- ConvertParam ReferenceSideConvertParam = null

## アセットシステムのアドオン検討　第1案　→　不採用

- アセットアドオン
    - 概要
        - アセットを表すアドオン。
        - アセットタイプ１種につき１つ作られる。
        - FBXならFBXで１つ。
        - ファイルである必要性はない。内部で使う一時的なデータもアセットで表すことがあるので。
    - 属性
        - IsOriginalFile : いわゆるアセットファイル。ユーザーがバージョン管理するもの。
        - IsIntermedidateData : 中間データ。コンバート時に生成されランタイムには直接載らないデータ。
        - IsRuntimeData : ランタイムデータ。ランタイムで扱うデータ。
        - IsRuntimeFile : ランタイムファイルになるデータ。
    - 要件
        - アセットタイプに関する情報を返す。
            - ファイルで扱うタイプかどうか。扱う場合は拡張子
        - エディタ上から設定できるプロパティの情報を返す

- アセットアドオンのプロパティ情報の例
    - AssetParam （例：AemdlFile.Scn)
        - Name：GfxScnAssetRef
        - DisplayName：シーン
        - Type：AssetRef<GfxScn>
        - Value：Hoge.fbx
    - 動的に変わる例（マテリアルセット） <- PropertyChangedイベントでパラメータを動的に変えることが可能
        - Name：MaterialSet
        - DisplayName：マテリアル設定
        - Type：Dictionary
        - Visibility：True
        - Value：
            - ["Face"] <- マテリアルが増減しても設定が維持されるように名前をキーとする
                - Name："Face"
                - DisplayName："Face" <- シーンのマテリアル名
                - Type：Dictionary
                - Value：
                    - ["GfxMatAssetRef"]
                        - Name：GfxMatAssetRef
                        - DisplayName："マテリアル"
                        - Type：AssetRef<GfxMat>
                        - Value：Face.aemat
                    - ["Params"]
                        - Name：Params
                        - DisplayName："パラメータ"
                        - Type：Dictionary
                        - Value：
                            - ["Color"]
                                - Name：Color
                                - DisplayName：”Color"
                                - Type：Color4
                                - Value：(RGBA)
                            - ["Texture"]
                                - Name：Texture
                                - DisplayName："Texture"
                                - Type：AssetRef<GfxTex>
                                - Value：Foo.tga
```
こうじゃなくて
================================
プロパティ 
================================
A.aemdl
--------------------------------
+Basis
   Scene            [Hoge.fbx  ]
+MaterialSetting
  +Face
     Material       [Face.aemat]
    +Params
       Color        [##########]
       Texture      [Foo.tga   ]
--------------------------------

こうなるといいよね
================================
プロパティ 
================================
A.aemdl
--------------------------------
+Basis
   Scene            [Hoge.fbx  ]
+MaterialSetting
  +Face
     Material       [Face.aemat]
       Color        [##########]
       Texture      [Foo.tga   ]
--------------------------------
```

- アセットコンバートアドオン
    - 概要
        - アセットを別のアセットに変換する機能を提供するクラス
            - 例： FbxFile を GfxTexBundle に変換する
        - 見通し切れていない＆シンプルにしたいので、入力出力１対のアセットタイプペアしか扱えないこととする。
        - 2段階コンバートは考えないことにする。
            - A <- B <- C
            - 欲しい場面があまり想像できないのと、回避策はあるので。
            - 例えばテクスチャ6枚使ってキューブマップテクスチャアセットを作るアセットを作ったとして。
                - GfxTexBundles <- Converter<GfxTexBundle>(CustomCubeTexAsset{AssetRef<GfxTexBundle>[6] texs})
                - というのでなんとかならんでもない。
    - 要件
        - 基本情報を返す
            - どのアセットをなんのアセットに変換するか
        - 渡されたアセットを別のアセットにコンバートをする
        - 渡されたアセットを別のアセットにコンバートする処理の依存情報を返す
    - もうちょっと具体的な要件
        - アセットを別のアセットタイプに変換できるか判定する
            - システム情報など出力データに必要な情報も一緒に渡される
            - 判定結果に含めるもの
                - 作成できるかどうかの真偽値
                - ランタイムファイルを出力する場合はファイルパス情報
                - 副産物として出力するアセットを0個以上
                    - デバッグ情報バイナリなどがここに当てはまる
                - 他のアセットも使う場合は依存アセット情報を0個以上
            - ランタイムアセットの出力パスについて
                - "Foo/Hoge.file" を指定した場合
                - アセットシステム側で衝突しないようにパスが加工される "$(Plugin)/Foo/Hoge.file" 
                - 最終出力先はハッシュパスになる "$(ProjectRoot)/.Cache/Adel.Asset/$(ハッシュパス)/$(依存情報パス).file
                - ↑のフォルダに直接書き込むとビルド中にエラーが起きると中途半端なデータとなってしまうおそれがある。
                    - なので　*.file.tmp という名前に書き込み、書き込みが終わったらアセットシステム側で *.file にリネームする。
        - 指定のアセットの作成に必要な情報を返す
            - 判定時に使ったアセットの情報もここで渡される
            - 返す情報
                - 依存情報
                    - 依存アセット
                    - 依存アセットコンバータ => バージョンが変わったら再ビルドする必要があるので
                    - 依存文字列
                        - エンディアン、ビット環境、実行モード、ビルドバージョンなどを元にコンバータが生成する任意の文字列
                        - ハッシュ計算で使われる
                - アセットコンバートタスク
                    - 依存アセットのビルドタスクもここに含める

- ResScnについて
    - 前はResMdlと呼んでいたヤツ。ボーンの親子階層、プリミティブ、メッシュの表示フラグなどの情報を含むもの。
    - カメラなどのアニメが必要になったらそれは ResCam や ResEnv など ResScn とは別の名前を付ける。

- 考えられていない点
    - ResShader を *.aemdl 単位で作ってしまってよいものか
        - シェーダーのセットアップはプラットフォームによってはわりと処理時間がかかるのでできる限り共通化したほうがいいのか否か。
        - aemat のアセット側コンバートパラメータで設定してしまおうか。
    - ランタイムスクリプトのモデルコンポーネントに GfxMdlBundle アセットを指定する流れ
        - ...
 
## アセットシステムのアドオン検討　第2案

第1案の枠を固めた後にUnity見たら非常にシンプルな印象を受けたのでもっとシンプルにしてみる。

第1案からの変更点
- アセットアドオンはアセットファイルに限定する。
    - 中間データクラスなどはアドオンと定義しなくてよい。DLL内にあるただのクラス。
- ランタイムで扱うデータはリソースと呼ぶ。コンバート前＝アセット。コンバート後＝リソース。
- ランタイムではリソースキー（ResourceKey）もしくはそれを派生したクラスを ResourceManager に渡すと欲しいリソースがもらえる。
- ResourceKey はエディタでアセットをスクリプトのプロパティに適用したら、リソースキーを生成してそれを使ってプロパティを設定する。
    - 詳しくは下の Texture の例を参照。
- コンバータはアセットtoリソース（ConvertToAsset）とアセットto開発キット情報オブジェクト（ConvertToDevkitInfo）の機能を提供する。
    - 入力のアセットタイプは1種類に限定。出力できるリソースや開発キット情報オブジェクトは複数対応して良い。
- コンバータの依存関係周りの仕様大枠は第1案から継承。

Texture
StaticTexture : Texture

MultiTextureAsset

TgaFile

TgaFileConverter
- CanConvertToResource<AdelEngine.Graphics.Texture>(...)
- ConvertToResource<AdelEngine.Graphics.Texture>(...) -> 
    Result {
        object ResourceKey; (GfxFileResourceKey)
        object DevkitInfo; null
    }
- ConvertToDevkitInfo<Adk.Graphics.TextureInfo>(...) ->
    Result {
        object Object; (TextureInfo)
    }
- AssetSideConvertParam
- ReferenceSideConvertParam

class HogeScript // ランタイムのスクリプトコード
{
    public Texture MyTex {get;set;} // エディタのプロパティ欄にTextureを設定できる項目が追加される。
}
ScriptComponent:
    TypeName: "HogeScript"
    Property:
        Target: "MyTex"
        RequireType: "AdelEngine.Graphics.Texture"
        AssignResource: 
            AssetPath: ./Hoge.tga
            AssetEntryPath: null # アセット内の項目（例：１つのFBXファイル内にある特定のモーション）を指定する場合に必要と予想して仮置き
            AssetKey: A067-932E-032B-E094

スクリプトコードで Texture MyTex プロパティが宣言されたら
- Texture が取得できる ResourceKey が実行時に必要。
- エディタでは CanConvertToResource<Texture> なアセットがここに設定可能。
- アセットビルドで ConvertToResource<Texture> が実行されてリソースが生成される。
- 設定したアセットの ResouceKey をランタイム時に使用して MyTex に Texture を設定する。

アセットのプロパティ（ReferenceSideConvertParam）で StaticTexture が宣言されたら。
- エディタでは CanConvertToDevkitInfo<StaticTexture> なアセットがここに設定可能。
- ConvertToDevkitInfo<StaticTexture, StaticTextureInfo>() で StaticTextureInfo オブジェクトにアクセスできる。

AematAssetConverter
- ConvertToDevkitInfo<MaterialSource, MaterialSourceInfo>() ->
    Result {
        object Object; (MaterialSourceInfo) {
            ...
            AdditionalInfo
                ShaderInfo Shader;
                StaticTextureInfo[] Textures;
        }
    }

FbxToSceneConverter
- ConvertToResource<SceneGraph>() ->
    Result {
        object ResourceKey; {GfxFileResourceKey}
        object DevkitInfo;
    }
- ConvertToDevkitInfo<SceneGraph, SceneGraphInfo>() ->
    Result {
        object Object; (SceneGraphInfo)
    }

AemdlConverter
- ConvertToResource<ModelSource>() ->
    Result {
        object ResourceKey; (GfxFileResourceKey)
        object DevkitInfo;
    }
- ConvertToDevkitInfo<ModelSource, ModelSourceInfo>() ->
    Result {
        object Object; (ModelSourceInfo)
    }

AdelEngine.Graphics
- Model (R/W)
    - ModelTransformState (Source:SceneGraph)
    - ModelVisibilityState (Source:SceneGraph)
    - ModelMaterialState* (Source:MaterialSource*)
- ModelSource (RO)
- SceneGraph (RO)
- Material (R/W)
- MaterialSource (RO)
- Texture (RO)
- StaticTexture (RO)
- RenderedTexture (RO)※ピクセル部はR/W
- Shader (RO)
※ R/W なクラスにインスタンス化するものは クラス名＋Source をつけてみる方針。

Adk.Graphics
- ModelSourceInfo
- SceneGraphInfo
- MaterialSourceInfo
- StaticTextureInfo
- ShaderInfo

ae::core::gfxapi (gfx_api?)
- Device
- CommandBuffer
- RenderState
- RenderTargetInfo
- Buffer
- VertexAttrView
- UniformBlockView
- StreamOutBlockView
- ScanBuffer
- FrameBuffer
- TextureView
- SamplerView
- ShaderProgramView
- StaticTextureResource
- ShaderResource
- VertexAttributeResource
- などといったクラス群。

ae::gfx AdelEngine.Graphics
- Model
- ModelSource
- Material
- Texture
- StaticTexture
- ...

ae::gfx::inside
- Resource
- ResModelSource
- ResSceneGraph
- ResMaterialSource
- ResStaticTexture

```c++
class ae::gfx::inside::Resource {
    Resource(byte_t* aBytes);
    void setup();
    void cleanup();

    ResModelSource   modelSource(...);
    ResStaticTexture staticTexture(...);
    ...
}
```
```c#
// namespace AdelEngine
public class ResourceKey {
}
public class FileResourceKey {    
    public FileKey FileKey;
}

// メモ：
// オリジナルの ResourceKey Resource ResourceRepos は
// ランタイムスクリプトコードとして追加可能。（プラグインも同様）

public class Graphics.GfxFileResourceKey : FileResourceKey {    
    public GfxResourceKind Kind;
    public string EntryName;
}
public class Graphics.GfxFileResource {
    public GfxFileResource(byte[] aBytes);
    public void Cleanup();

    public ModelSource ModelSource(...);
    ...

    NativeClass< AdelEngineNative.Gfx.Inside.Resource > _Resource;
}
internal class Graphics.GfxFileResourceRepos : ResourceReposBase {
    public object Get<TResult>(ResourceKey aKey)
    {
        GfxFileResource res = null;
        if (_Files.Contains(aKey)) {
            res = _Files[aKey];
        } else {
            _Files.Add(aKey, new GfxFileResource(FileManager.GetBytes(aKey)));
        }

        ...

        return ...;
    }
    public void CleanupResourceDependFile(FileKey aFileKey);
    Dictionary<FileResourceKey, GfxFileResource> _Files;
}
public static class ResourceManager {
    public object GetResource<TResult>(TResourceKey aKey)
    {
        // TResult = Texture
        // TResourceKey = GfxFileResourceKey
        return _ResourceRepos[TResourceKey.TypeInfo()].Get<TResult>(aKey);
    }

    public void CleanupResourceDependFile(FileKey aFileKey);
}
public static class FileManager {
    public bytes[] GetBytes(FileKey aKey);
}
```
