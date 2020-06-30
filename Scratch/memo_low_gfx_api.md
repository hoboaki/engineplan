# 3D グラフィックス低レベル API に関するメモ

この資料はクロスプラットフォームな 3D グラフィックスライブラリを検討する個人的な資料です。各グラフィックスライブラリの差異をまとめたり，クロスプラットフォームなライブラリの設計や最適化に関するメモを書き残します。

## コマンドバッファで設定する単位

### 個別メモ

### Vulkan

★ マークがあるところは他の箇所と値を一致させる必要あり。

- RenderPassBegin（レンダーターゲットクリアのトリガーも担う）
  - レンダーパス（★2）
    - レンダーターゲットのフォーマット（★1）
    - loadOp storeOp
  - レンダーターゲット（★1）
  - レンダーエリア
    - https://qiita.com/Pctg-x8/items/2b3d5c8a861f42aa533f
  - レンダーターゲットクリアカラー
- パイプライン（※マークがあるものは直接設定の API もある）
  - レンダーパス（★2）
  - シェーダー
  - 頂点バッファレイアウト
  - プリミティブトポロジ
  - ビューポート※
  - シザー矩形※
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias 系
  - マルチサンプリングオプション
  - デプスステンシルステート
  - ブレントステート
  - ブレンド係数カラー値※
  - パイプラインレイアウト（シェーダーバインド宣言）（★3）
    - ディスクリプタセットレイアウト配列（★4）
      - コンスタントバッファビュー（ユニフォームバッファ）の宣言
      - ストレージバッファビューの宣言
      - サンプラーの宣言
    - インラインコンスタントデータの宣言（PushConstant）（★5）
- ディスプリプタセット配列（シェーダーバインド実体）（★4）
  - コンスタントバッファビュー（ユニフォームバッファ）
  - テクスチャビュー（イメージビュー）
  - ストレージバッファビュー
  - サンプラー
  - パイプラインレイアウト（★3）
- その他の直接設定
  - ビューポート（VK_DYNAMIC_STATE_VIEWPORT が有効なパイプラインの場合）
  - シザー矩形（VK_DYNAMIC_STATE_SCISSOR が有効なパイプラインの場合）
  - ステンシルテスト参照値
  - ブレンド係数カラー値
  - プリミティブトポロジ（VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT が有効なパイプラインの場合）
  - 頂点バッファ・インデックスバッファ
  - インラインコンスタントデータ（PushConstants）（★5）
  - 他にも DYNAMIC_STATE で指定されたものが設定可能
- トリガー
  - 描画系
  - コンピュート

### DirectX 12（コマンドリスト）

★ マークがあるところは他の箇所と値を一致させる必要あり。

- パイプラインステート
  - ルートシグネチャのポインタ（★1）
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias 系
  - マルチサンプリングオプション
  - デプスステンシルステート
  - ブレンドステート
  - 頂点バッファレイアウト
  - 頂点シェーダー
  - ピクセルシェーダー
  - プリミティブトポロジタイプ（点, 線, 三角形）（★3）
  - レンダーターゲットのフォーマット（★2）
- ルートシグネチャ（=シェーダーバインド宣言＆実体）（★1）
  - コンスタントバッファビュー
  - テクスチャビュー（シェーダーリソースビュー）
  - サンプラー
  - ストレージバッファビュー（UAV:unordered access view）
- その他の直接設定
  - レンダーターゲット設定（★2）
  - ビューポート
  - シザー矩形
  - ブレンド係数カラー値
  - ステンシルテスト参照値
  - プリミティブトポロジ（★3）
  - 頂点バッファ・インデックスバッファ
- トリガー
  - レンダーターゲットのクリア
  - 描画系

**パイプラインステートのシリアライズ**

https://shobomaru.wordpress.com/2015/07/22/d3d12-pipeline-state/

ルートシグネチャへのポインタがありますけどシリアライズとは・・・？

### Metal（コマンドエンコーダ）

- レンダーパス（これを引数にコマンドエンコーダを作成・レンダーターゲットクリアのトリガーも担う）
  - レンダーターゲット
  - loadOp storeOp
  - レンダーターゲットクリアカラー
- パイプラインステート（RenderPipeline/ComputePipeline）
  - シェーダー
  - 頂点バッファレイアウト
  - レンダーターゲットのフォーマット
  - マルチサンプリングオプション
  - コンスタントバッファビューの書き込み可能属性指定（なにこれ？）
- アーギュメントバッファ（全部指定する必要なし・シェーダーバインド宣言＆実体として扱い可能）
  - コンスタントバッファビュー（MTLBuffer : MTLResource）
  - テクスチャビュー（MTLTexture : MTLResource）
  - サンプラー（MTLSamplerState）
  - インラインコンスタントデータ
- その他の直接設定
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias 系
  - デプスステンシルステート
  - ブレントステート
  - アーギュメントバッファで指定できる各パラメータ
  - ビューポート
  - シザー矩形
  - ブレンド係数カラー値
  - ステンシルテスト参照値
  - 頂点バッファ・インデックスバッファ
- トリガー
  - 描画系（プリミティブトポロジは引数で指定）
  - コンピュート

## セカンダリコマンドバッファ

### 個別メモ

- 基本的に各ライブラリは何かしらの形式でセカンダリまではサポートしている。
- 今まで１つの大きなプライマリにたくさんのセカンダリを挿入する設計しか考えてこなかったが，オーバーヘッドがそこまで大きくないのならプライマリももっと細かくすれば更に最適化できそうな気がしてきた。

### Vulkan

- 普通の仕様。
- https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdExecuteCommands.html

### DirectX 12

- 一部制約があるがだいたい普通。
- [ID3D12GraphicsCommandList::ExecuteBundle](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12graphicscommandlist-executebundle)

### Metal

- 通常のコマンドバッファと区別化されている。IndirectCommandBuffer。
- IndirectCommandBuffer 内から IndirectCommandBuffer はコールできない。
- RenderCommandEncoder/ComputeCommandEncoder に生成済の IndirectCommandBuffer を挿入できる。
- IndirectCommandBuffer で扱える設定項目も限定的。デプスステンシルステートやブレンドステートなどは扱えない。他 2 種 API と比べると扱いづらそう。
- ちなみに MoltenVk では Queue::submit() のタイミングでそれまでにコマンドバッファにつまれていた内容を Metal コマンドバッファとして再生成しているためこの制約にとらわれない。オーバーヘッドはあるが API としては互換がとれている。賢い。

## インダイレクト引数描画

### 個別メモ

- 全て同じように機能はそろっている。

### Vulkan

- [vkCmdDrawIndexedIndirect](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdDrawIndexedIndirect.html)

### DirectX 12

- [ID3D12GraphicsCommandList::ExecuteIndirect](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12graphicscommandlist-executeindirect)

### Metal

- https://developer.apple.com/documentation/metal/mtlrendercommandencoder/specifying_drawing_and_dispatch_arguments_indirectly

## 非同期コンピュート＆同期

### 個別メモ

- 同期は仕様をちゃんと考える必要あり。まずここの見通しをたてた上で他のところやったほうが良さそう。

### Vulkan

- メイン Queue とは別の専用の Queue を用意することで実現。
- [優先度設定](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-priority)もあり。メイン Queue より低い優先度で実行といったことも可能。0.0f〜1.0f で指定し値が大きい方が高優先。
- Queue 間の同期
  - セマフォ：Queue Family の制限は受けない。コマンドバッファの途中に挟めない。
  - イベント：同じ Queue Family で使用可能。コマンドバッファの途中に挟める。
- コマンドバッファ内の同期：パイプラインバリア
  - A の処理を B までに終わらせておいてね、的な感じで書ける。（[解説サイト 1](https://gpuopen.com/learn/vulkan-barriers-explained/)　[解説サイト 2](https://glhub.blogspot.com/2017/11/vulkan-vkcmdpipelinebarriervkpipelinest.html)）
  - 更に引数プロパティの MemoryBarrier、BufferMemoryBarrier, ImageMemoryBarrier で対象となるリソースや遷移（DX12 の TransitionBarrier/AliasBarrier に相当）を指定してバリアをはれる。
  - サンプルが少なくて理解が難しい。

### DirectX 12

- Vulkan と同様に Queue を２つ作る方式。
- [優先度](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_command_queue_priority)は NORMAL、HIGH、GLOBAL_REALTIM の３種類。
- Queue 間の同期はフェンス。
  - フェンス：コマンドバッファの途中に挟めない。
- コマンドバッファ内の同期はバリア。
  - [参考](https://docs.microsoft.com/ja-jp/windows/win32/direct3d12/using-resource-barriers-to-synchronize-resource-states-in-direct3d-12#split-barriers)
  - TransitionBarrier：レンダーターゲットが読み取りテクスチャになるよといった状態遷移を扱うバリア。
  - AliasingBarrier：A という Resource オブジェクトがこれ以降で B という Resouce オブジェクトとして使われることを宣言するバリア。
  - UavBarrier：ストレージバッファの読み書き処理をここまでに終わらせてというバリア。Dispatch した結果を別の Dispatch で参照する場合に使う。
  - 各種バリアに分割バリアという指定方式もある。ここからこの区間で完了させておいてねーという宣言ができ、パイプラインの最適化のヒントとなる。

### Metal

- [Queue を２つ作成](https://developer.apple.com/documentation/metal/synchronization/synchronizing_events_within_a_single_device)するのは一緒。
- 優先度設定は見つからなかった。
- Queue 間の同期はイベント。
  - [イベント](https://developer.apple.com/documentation/metal/mtlevent)：コマンドバッファ（コマンドエンコーダ）の途中に挟めない。
- コマンドバッファ内・コマンドバッファ間の同期はフェンス・バリア。
  - [フェンス](https://developer.apple.com/documentation/metal/mtlfence)：DX12 でいう AliasingBarrier と同じ。MTLHeap（メモリプール）を使って手動でリソースメモリ管理をして同じアドレスに別リソースオブジェクトを割り当てているときに使う。
  - バリア：ここまでに特定のリソースに対しての処理や特定のパイプラインステージに対する処理を終わらせてという宣言。

## 参考

- [A Comparison of Modern Graphics APIs](https://alain.xyz/blog/comparison-of-modern-graphics-apis)
