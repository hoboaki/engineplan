# 文字コード：UTF-8

## ロムの名前

意識するポイント
- ファイル名順＝歴史順でソートされる。
- ファイル名はできる範囲で短く。

変えられるようにする。（GitだとVcsVersionが手前にくるとファイル名順＝歴史順ではなくなるため）

svn
```
$(ProjectName)_$(VcsVersion)_$(BuildVersionShortName)_$(BuildTargetName)_$(BuildDateAndTime)

MyProject_r12345_Td_PC-Product_170401-1230
MyProject_r12345_Td_PC-Trial_170401-1230
```

git その１
```
$(ProjectName)_$(VcsLastModifiedDateAndTime)_$(BuildVersionShortName)_$(BuildTargetName)

MyProject_170401-1120_Td_PC-Product
MyProject_170401-1120_Td_PC-Trial
```

git その２
```
$(ProjectName)_$(VcsLastModifiedDateAndTime)_$(BuildVersionShortName)_$(BuildTargetName_$(VcsVersion)

MyProject_170401-1120_Td_PC-Product_AB0926
MyProject_170401-1120_Td_PC-Trial_AB0926
```

## 名前空間

公式コードの名前空間。予約名扱いのためユーザーコードではこの名前空間以下にコードを書いてはいけない。

C++

- ae:: 共通コード層。いかなる環境でも通るコードを書くことを意識する層。
- ap:: プラグインコード層。
- apf:: プラグイン共通コード層。プラグインコードで使い回される共通コードを書く層。（例：OpenGLの実装など）


C#

- Ae Ap Apf  : スクリプトコードから参照できるコード置き場。(limited-cs)
- Adk : スクリプトコードをのぞくC#コードから参照できるコード置き場。
- AdkExt : プラグインによるAdk拡張。

- ae   adel engine
- ap   adel engine plugin
- apf  adel engine plugin foundation
- adk  adel engine development kit

NativeCode(c++,objective-c) ae::* ap_* apf_*
ScriptCode(limited-cs) Ae.* Ap.* Apf.*
DevkitCode(cs) Adk.* AdkExt.*

Universalアセットのプラグイン構成
::ap_cut_scene::ScenePlayer
Ap.CutScene.ScenePlayer
AdkExt.CutScene.AssetCutScene

## 名前検討欄

- Platform
    - win-dx11
    - ios-gles300
- Build Target
- Build System
    - Win-VisualStudio Ios-Xcode Mac-Xcode
- Build Version
    - Debug(Db)
    - LocalDevelop(Ld) 
    - TeamDevelop(Td)
    - Review(Rv)
    - Final(Fn)
- Version Control System (Vcs)
- DirectX
    - dx11
- OpenGL
    - gl330 (version 3.3) gles300(version 3.0)

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
    - Ae.Gfx.ResMdl
    - Ae.Gfx.ResMdlAnimSkl
- .aemat .aematanim MaterialEditor
    - Ae.Gfx.ResMat
    - Ae.Gfx.ResMatAnim
- .aepfx PosteffectEditor
    - Ae.Gfx.ResPfx Ae.Gfx.ResPfxAnim
- .aevfx VfxEditor
    - Ae.Gfx.ResVfx
- .tga .dds
    - Ae.Gfx.ResTexture
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
        - ビルド済みアセットのファイルリスト（アセットのビルドはアセットシステムが行う）
        - ネイティブコードのリスト
        - システムインクルードパスのリスト
        - 作業に使うフォルダのパス
            - $(ProjectRoot)/.Build/$(Plugin) => これ以下をどう使うかはプラグインの自由
            - DevkitWinだとこういうフォルダを下に作る
                - /$(Platform)_$(BuildTarget)_$(BuildVersion)/Edt (エディットモード)
                - /$(Platform)_$(BuildTarget)_$(BuildVersion)/App (アプリケーションモード)
                    - /Exec => 実行ファイルフォルダ（成果物置き場・起動時にCodeとData以下からコピーされる）
                    - /Code => コードビルド領域
                    - /Data => データコピー領域
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
        - ビルダーアドオンは開発キットによって AssetBuild されたビルド済アセットを使って実行ファイルをビルドするアドオン、と呼べそう。

## アセットシステムの検討

- アセットシステムが使うフォルダ
    - $(ProjectRoot)/.Build/Adel.Asset
        - /Hash.db => 各アセットファイル（コンバート前のファイル）のデータハッシュ値DB
        - /$(ビルド済アセットファイルパスのハッシュ値) => 対象アセットのビルドで使える領域
    - $(ProjectRoot)/.Build/$(Plugin) (例：Adel.Fbx)
        - プラグインのワーク領域（どう使うかはプラグインに任される）
    - $(ProjectRoot)/.Cache
        - /Adel.Asset/$(ビルド済アセットファイルパスのハッシュ値)/$(アセット依存情報のハッシュ値).file
- アセットのビルド作業フォルダ＆キャッシュフォルダに関する補足
    - プラットフォーム名やビルドターゲット名はパスには含めなくてよい
        - それらの情報はアセット依存情報のハッシュ値に含まれているから。
    - ファイルパスのハッシュ値は64bit。
        - FAT32でも大丈夫なようにしたいので1フォルダあたり0xFFFF エントリーまで。
        - ファイルパスもその単位で区切るようにする。
        - 例：ファイルパスのハッシュ値が 0x0123456789ABCDEF 、依存情報のハッシュ値が 1010202030304040 の場合
            - /.Cache/Adel.Asset/0123/4567/89AB/CDEF/1010202030304040.file 
    
- アセットのリビルドの必要性が確認されたら
    - キャッシュサーバーへの問い合わせ
    - ビルド済みバイナリがあった場合
        - キャッシュサーバーからビルド済みのアセットを入手
    - ビルド済みバイナリがなかった場合
        - アセットビルドタスクをつむ
    - 実行ファイルにアセットの新しいバイナリのファイルパスを通知する (.Cache/File 以下のファイルパス)

- キャッシュフォルダについて
    - $(ProjectRoot)/.Cache
    - ここ以下のファイル達はキャッシュサーバーと通信してデータをアップロード＆ダウンロードする。
    - 目的は、同じアセットのビルドを他のPCで行わないようにし、ビルド時間を短縮化させるため。
    - 実行ファイルのビルドのキャッシュもできて良いかもしれないので、アセットビルドに限定しない構成にしておく。

