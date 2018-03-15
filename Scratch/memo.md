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
    - 開発キットコード DevKitCode
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
- AdelDevKit : 開発キットコード用コード置き場。（cs）

- ae   adel engine
- adk  adel engine development kit

NativeCode(c++,objective-c) ae::* ae_* (公式プラグインはこの形式) 
ScriptCode(limited-cs) AdelEngine.*
DevKitCode(cs) AdelDevKit.*

プラットフォーム非依存アセットのプラグイン構成
::ae_cut_scene::ScenePlayer
AdelEngine.CutScene.ScenePlayer
AdelDevKit.CutScene.AssetCutScene
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
    - Local(Lc) 
    - Inside(Is)
    - Preview(Pr)
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
- Android
    - Andrd   AdelBuildKitAndrd   ae_andrd_os ← これかなー
    - Andro   AdelBuildKitAndro   ae_andro_os
    - Android AdelBuildKitAndroid ae_android_os

## グラフィックス世代の扱い

２つで考える
- SM3 VERT+FRAG GLES3ベース
    - GL3.3[Win, Mac] GLES3[iOS, Android] (DX9-10[Win])
- SM5 SM3＋GEOM+GPGPU （コマンドバッファ並列化の有無は別枠）
    - Metal[Mac, iOS] Vulkan[Win, Android] (GL4.3[Win]) (DX11 [Win])
    - Mac は GL3.3 の次は GL4.1 （中途半端）
    - Mac で GL4.3 使えるならそこまで対応しようかと思ったけども難しいなら 4.3 サポートは後回しかな。

## NativeCode フォルダ構成検討

- ae
    - base
    - gfx (旧 ae::g3d 相当)
    - core
        - os_api
        - os_impl
        - gfx_api
        - gfx_impl
        - snd_api
        - snd_impl

ae::core::gfx_api::CommandBuffer
ae::core::gfx_impl::CommandBufferImpl
ae_open_gl::CommandBufferImpl
namespace ae {
namespace core {
namespace gfx_impl = ::ae_open_gl;
}}

ae::core::snd_api::Hoge
ae::core::snd_impl::HogeImpl
ae_open_al::HogeImpl
namespace ae {
namespace core {
namespace snd_impl = ::ae_open_al;
}}

```c++
// ae/core/gfx_api/CommandBuffer.hpp

// コンパイル時に渡されるマクロ
#define AE_CORE_GFX_IMPL_DIR ae_open_gl
#define AE_CORE_GFX_IMPL_NAMESPACE ::ae_open_gl

// マクロを使ってインクルード
#define AE_INCLUDE_PATH(x) <x>
#include AE_INCLUDE_PATH(AE_CORE_GFX_IMPL_DIR/CommandBufferImpl.hpp)

// gfx_impl 先を確定
namespace ae {
namespace core {
namespace gfx_impl = AE_CORE_GFX_IMPL_NAMESPACE;
}}

// クラス定義
namespace ae {
namespace core {
namespace gfx_api {
class CommandBuffer
{
private:
    gfx_impl::CommandBufferImpl mImpl;
}
}}}
```
