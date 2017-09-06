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
