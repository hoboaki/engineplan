# プラグインやそれに関わるシステム関連のメモ

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

## プラグインでできること

- BuildSystem の追加
- CoreLib の追加
- Vcs の追加
- ネイティブコード の追加
- スクリプトコード の追加
- アセットタイプ の追加
- 既存アセットタイプに独自パラメータの追加
- エディタツールバーのメニュー追加
- エディタサブウィンドウの追加

# 用語

- コード
    - ネイティブコード NativeCode
        - 製品にのるコード。(c++ objective-c)
    - スクリプトコード ScriptCode
        - 製品にのるコード。(limited-cs)
    - 開発キットコード DevkitCode
        - コマンドラインモードとエディットモードで動作するコード。（cs)
- 実行モード
    - エディットモード
        - エディタと通信しながらゲームを実行するモード。
    - アプリケーションモード
        - エディタと通信せずゲームを実行するモード。

## タスク

ビルド
- Vcs更新
- Clean
- Build
    - Asset
    - ScriptCode
    - NativeCode

- Vp Vcs処理
- Ab アセットビルド（Vcs処理待ち）
    - FbxセットA
        - バイナライズ
            - Tex->ResTex Mat->ResMat Fbx->ResMdl
        - パック
    - ScriptCode
- Eb 実行ファイルビルド（アセットビルド待ち）

- タスクコマンド状態
    - Wait
    - Prepared
    - Executed
    - Finished
    - Canceled

- タスク
    - A
        - A-1 A-2 A-3
    - B

## ビルドシステムのビルダーアドオン要件

- ビルドターゲットのシステム情報を返す
    - [32bit, 64bit] [LE, BE]
- リビルドする必要性があるかの情報を返す
- 実行ファイルをビルドする
    - エディットモード アプリケーションモード
    - ビルド時に渡される情報
        - ビルドターゲット情報
        - ランタイムアセットのファイルリスト（アセットのビルドはアセットシステムが行う）
        - ネイティブコードのリスト
        - システムインクルードパスのリスト
        - 作業に使うフォルダのパス
            - $(ProjectRoot)/.Build/$(Plugin) => これ以下をどう使うかはプラグインの自由
            - DevkitWinだとこういうフォルダを下に作る
                - /$(Platform)_$(BuildTarget)_$(BuildVersion)/Edt (エディットモード)
                - /$(Platform)_$(BuildTarget)_$(BuildVersion)/App (アプリケーションモード)
                    - /Exec => 実行ファイルフォルダ（成果物置き場・起動時にCodeとData以下からコピーされる）
                    - /Code => コードビルド領域
                    - /Data => データコピー領域（エディットモードの.Cacheから直接リードするため空）
                - 例: MyProject/.Build/Adel.DevkitWin/Win-Dx11_PC-Product_Ld
- ビルドした実行ファイルを起動する
- 実行中の実行ファイルを停止する
- ビルドした実行ファイルを発行（Publish）する
    - 指定ディレクトリにアプリケーションモードの実行ファイルパッケージを配置する

- ビルドフォルダについて
    - $(ProjectRoot)/.Build
    - 実行ファイルやアセットのビルドのワーク領域として使うフォルダ。

- 考えられていない点
    - アセットのビルドフォルダと並べてみて違和感がないか -> 検討済み
    - アセットのビルドの"ビルド"の言葉かぶりが気になる。
        - 各所でビルドという言葉を使うため、短いにこしたことはないし、
        - ビルド = 全体を創り上げるというイメージも合っているし。
        - アセットビルドという言葉も合っている。違和感ない。
        - ビルドする → アセットと実行ファイルをビルドする 、という構成とするとしっくり。
        - となると、実行ファイルをビルドする機構をちゃんと名前付けしてあげれば違和感はとけそう。
        - AssetBuild と ExecFileBuild 
        - ビルダーアドオンは開発キットによって AssetBuild されたランタイムアセットを使って実行ファイルをビルドするアドオン、と呼べそう。

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
    - アセット・アセットファイル
        - Asset 以下に配置されるファイル
    - アセットタイプ
        - アセットのファイルタイプ。
    - ランタイムアセット・ランタイムアセットファイル
        - アセットファイルをランタイム用にビルドしたアセット。１つのアセットから２つのファイルが出力されることもある。
    - ランタイムアセットタイプ
        - ランタイムアセットのファイルタイプ。
    - 組み込みリソース
        - 非アセットファイルをランタイム用にビルドしたファイル。
    - アセットビルダー
        - アセットをランタイムアセットにする機能。
    - アセットコンバータ
        - アセットを別のアセットに変換する機能。

- アセットアドオン
    - 概要
        - アセットを表すアドオン。
        - アセットタイプ１種につき１つ作られる。
        - FBXならFBXで１つ。
        - ファイルである必要性はない。内部で使う一時的なデータもアセットで表すことがあるので。
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
     Color          [##########]
     Texture        [Foo.tga   ]
--------------------------------
```

- ランタイムアセットアドオン
    - 概要
        - ランタイムアセットタイプ１種につき１つ作られる。
        - バイナリデータとデバッグ用バイナリデータ２つ作られるアセットの場合は２つアドオンを用意する。

- アセットビルダーアドオン
    - 要件
        - アセットファイルを指定のランタイムアセットタイプを作成できるか判定する
            - システム情報など出力データに必要な情報も一緒に渡される
            - 判定結果に含めるもの
                - 作成できるかどうかの真偽値
                - 作成できる場合は出力するランタイムアセットファイル情報（ランタイムアセットファイルパスなど）を１つ
                - 副産物として出力するランタイムアセットファイル情報を0個以上
                    - デバッグ情報バイナリなどがここに当てはまる
                - 他のランタイムアセットも使う場合は依存ランタイムアセット情報を0個以上
                    - ここでいう依存ランタイムアセット情報とはランタイムアセットタイプとアセットファイルのペア。
            - ランタイムアセットの出力パスについて
                - "Foo/Hoge.file" を指定した場合
                - アセットシステム側で衝突しないようにパスが加工される "$(Plugin)/Foo/Hoge.file" 
                - 最終出力先はハッシュパスになる "$(ProjectRoot)/.Cache/Adel.Asset/$(ハッシュパス)/$(依存情報パス).file
                - ↑のフォルダに直接書き込むとビルド中にエラーが起きると中途半端なデータとなってしまうおそれがある。
                    - なので　*.file.tmp という名前に書き込み、書き込みが終わったらアセットシステム側で *.file にリネームする。
        - 指定のランタイムアセットファイルの作成に必要な情報を返す
            - 判定時に使ったアセットファイルの情報もここで渡される
            - 返す情報
                - 依存情報
                    - 依存アセット
                    - 依存ランタイムアセット => （そのランタイムアセットの依存情報も加えられる）
                    - 依存リソースファイルパス => 非アセットの依存ファイルパス
                    - 依存アセットビルダー => バージョンが変わったら再ビルドする必要があるので
                    - 依存アセットコンバータ => バージョンが変わったら再ビルドする必要があるので
                    - 依存文字列
                        - エンディアン、ビット環境、実行モード、ビルドバージョンなどを元にコンバータが生成する任意の文字列
                        - ハッシュ計算で使われる
                - アセットビルドタスク
                    - 依存ランタイムアセットのビルドタスクもここに含める

- アセットコンバータアドオン
    - 概要
        - アセットを別のアセットに変換する機能を提供するクラス
            - 例： FbxFile を GfxTex に変換する
        - FBXプラグインはおそらくアセットコンバータのみ提供しアセットビルダーは提供しない。
            - アセットビルダーは GfxTex を扱うプラグインが提供しているはずなので。
        - 2段階コンバートは考えないことにする。
            - A <- B <- C
            - 欲しい場面があまり想像できないのと、回避策はあるので。
            - 例えばテクスチャ6枚使ってキューブマップテクスチャアセットを作るアセットを作ったとして。
                - GfxTex <- Converter<GfxTex>(CustomCubeTexAsset{AssetRef<GfxTex>[6] texs})
                - というのでなんとかならんでもない。
    - 要件
        - コンバータの情報を返す
            - どのアセットをなんのアセットに変換するか
        - 渡されたアセットを別のアセットにコンバートをする
        - 渡されたアセットを別のアセットにコンバートする処理の依存情報を返す

- （合わせて考えた方がイメージしやすいのでモデルのデータフローを検討する）
- *.aemdl -> Ae.Gfx.ResBin(Ae.Gfx.ResMdl -> ResScn,ResMat,ResTex への参照情報)
    - シーン（*.fbx *.dae） -> Ae.Gfx.ResBin(Ae.Gfx.ResScn 1つ)
        - 他の *.aemdl で同じモデルシーンを参照してもバイナリは１つで済む。
    - マテリアル達（*.aemat） -> Ae.Gfx.ResBin(Ae.Gfx.ResMat Ae.Gfx.ResShd それぞれ1つ以上)
        - ほとんどのケースでは１aemdlファイルにつき１つバイナリが生成される。（同一なマテリアルパラメータのケースがあればバイナリが共有される）
        - マテリアルパラメータ（アセットプロパティとして編集）
            - シェーダーパラメータ
            - テクスチャ -> Ae.Gfx.ResBin(Ae.Gfx.ResTex)
- *.aemdl をビルドする際のプロセス
    - モデルバイナリの作成
        - シーンバイナリ、マテリアルバイナリ、テクスチャバイナリのパスを取得＆埋め込む。
    - シーンバイナリの作成
        - *.fbx or *.dae を中間シーンデータに変換。
        - CoreGfx の シーンバイナライザ を使ってバイナリを作成。
    - マテリアルバイナリの作成
        - CoreGfx の シェーダバイナライザ を使ってバイナリを作成。
        - CoreGfx の マテリアルバイナライザ を使ってバイナリを作成。
    - テクスチャバイナリの作成
        - CoreGfx の テクスチャバイナライザ を使ってバイナリを作成。
- これをアドオンに当てはめる
    - アセットアドオン
        - モデルファイル
            - Adk.Asset.GfxMdl
            - AdkExt.StdGfx.Asset.AemdlFile
        - シーンファイル
            - Adk.Asset.GfxScn
            - AdkExt.StdGfx.Asset.FbxFile
        - マテリアル
            - Adk.Asset.GfxMat
            - Adk.Asset.GfxShd
            - AdkExt.MaterialEditor.Asset.AematFile
        - テクスチャ
            - Adk.Asset.GfxTex
            - AdkExt.StdGfx.Asset.TgaFile
    - ランタイムアセットアドオン
        - モデルバイナリ = Adk.RuntimeAsset.GfxResMdl
        - シーンバイナリ = Adk.RuntimeAsset.GfxResScn
        - マテリアルバイナリ = Adk.RuntimeAsset.GfxResMat
        - テクスチャバイナリ = Adk.RuntimeAsset.GfxResTex
        - シェーダバイナリ = Adk.RuntimeAsset.GfxResShd (今回は使わない)
    - A.aemdl が欲しいバイナリ
        - Mdl.bin
            - 依存情報
                - 依存バイナリ： Scn.bin MatSet.bin Tex.bin
                - 依存文字列：GfxConverterの情報
                - 要検討：ランタイムアセットパスが変わらない限りリビルドの必要性ないはずだけど
            - タスク
                - Scn.bin MatSet.bin Tex.bin のランタイムアセットパスを使ってバイナリ化
        - Scn.bin
            - 依存情報　IAssetConverter<GfxScn> の依存情報 FbxToGfxScn(Hoge.fbx))
                - 依存アセット：Hoge.fbx
                - 依存コンバータ: FbxToGfxScnConverter
                - 依存文字列：GfxConverterの情報
            - タスク
                - IAssetConverterでFbxをGfxScnデータにコンバートして取得
                - GfxScn を ランタイムアセットにビルド
        - MatSet.bin 
            - 依存情報 AdelGfxConverter(AdmatToGfxMat(Face.admat))
                - 依存アセット：Face.admat
                - 依存コンバータ：AdmatToGfxMatコンバータ
                - 依存文字列：GfxConverterの情報
            - タスク
                - Face.mdmat を GfxMat にコンバート（GfxShdも抱えているGfxMatが得られる）
                - GfxMatSet (GfxMat GfxShd) を１つのランタイムアセットにビルド
        - Tex.bin
            - 依存情報 AdelGfxConverter(TgaToGfxTex(Foo.tga))
                - 依存アセット：Foo.tga
                - 依存コンバータ：TgaToGfxTex
                - 依存文字列：GfxConverterの情報
            - タスク
                - Foo.tga を GfxTex にコンバート
                - GfxTex をランタイムアセットにビルド
    - Aemdl アセットのプロパティ
        - AssetRef<GfxScn> scene; <= FbxToGfxScnConverter(fbxAsset)
        - List<MaterialHolder> MaterialHolderss
            - "MatA" (Key)
                - AssetRef<Adk.Asset.GfxMat> material; <= AematToGfxMatConverter(aematAsset)
                - MaterialParamHolders
                    - "Color"
                        - color4(RGBA)
                    - "Texture"
                        - AssetRef<Adk.Asset.GfxTex> <= TgaToGfxTexConverter(tgaAsset)

- ResScnについて
    - 前はResMdlと呼んでいたヤツ。ボーンの親子階層、プリミティブ、メッシュの表示フラグなどの情報を含むもの。
    - カメラなどのアニメが必要になったらそれは ResCam や ResEnv など ResScn とは別の名前を付ける。


- 考えられていない点
    - ResShader を *.aemdl 単位で作ってしまってよいものか
        - シェーダーのセットアップはプラットフォームによってはわりと処理時間がかかるのでできる限り共通化したほうがいいのか否か

