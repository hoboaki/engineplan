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
- 公式○○（公式コード・公式プラグイン）
    - AdelEngineチームが作成し提供するもの。

## 名前空間

公式コードの名前空間。予約名扱いのためユーザーコードではこの名前空間以下にコードを書いてはいけない。

C++

- ae:: 共通コード層。いかなる環境でも通るコードを書くことを意識する層。


C#

- AdelEngine : スクリプトコードから参照できるコード置き場。(limited-cs)
    - Ae に略そうかと思った時期もあったが、C#なら名前空間は分かりやすさ重視だろう判断でフルネームにした。
- Adk : 開発キットコード用コード置き場。（cs）

- ae   adel engine
- adk  adel engine development kit

NativeCode(c++,objective-c) ae::* ae_* (公式プラグインはこの形式) 
ScriptCode(limited-cs) AdelEngine.*
DevkitCode(cs) Adk.*

プラットフォーム非依存アセットのプラグイン構成
::ae_cut_scene::ScenePlayer
AdelEngine.CutScene.ScenePlayer
Adk.CutScene.AssetCutScene
※公式プラグインは名前空間がかぶることはないはずなので名前空間は分けない。

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
    - dx11 Dx11
- OpenGL
    - gl330 (version 3.3) gles300(version 3.0)
    - Gl330 Gles300
- Vulkan
    - vk
    - Vk
