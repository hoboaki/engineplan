# Adel Engine Low Graphics Api マニュアル

## はじめに

このマニュアルでは ae::gfx_low モジュールについての概要を記述します。
このマニュアルはグラフィックスAPIを使ったプログラミングの経験者の人が理解できるレベルの内容を想定しています。
もしそういった経験がない人はまず DirectX や Vulkan などで基本を抑えることをオススメします。

また、実際のコードの書き方は各サンプルを見てください。

## ae::gfx_low について

ae::gfx_low は低レベルグラフィックスライブラリをラップするAPI郡で、Vulkan、DirectX12、Metal に対しての抽象化に対応する思想で作られています。

現在は Vulkan に対してのみ実装されています。

便利機能は基本的にないためユーザー側で必要に応じて用意してください。

## 基本的なオブジェクト

ae::gfx_low を使う上でまず以下のオブジェクトを作ることになります。

### System

何よりも先に作る必要があるオブジェクトです。
１実行アプリケーションにつき１つ作成してください。

### Device

１つのGPUデバイスに対応するオブジェクトです。
普通の使い方ですと１つだけ作ればOKです。
本オブジェクトを通してGPUデバイスの情報を取得したりグラフィックスに関連するメモリの確保・解放を行ったりします。
本オブジェクトを作成する際に、後述の Queue も一緒に作成されます。

### Queue

コマンドを流し込むキューです。
後述の CommandBuffer を本オブジェクトに渡すことでGPUで処理されます。
最低１つ作成し、非同期コンピュートなどをする場合は必要に応じて２つ以上作成します。

### CommandBuffer

GPUに投げるコマンド（＝処理）を書き込むバッファです。
書き込まれたバッファは本オブジェクトを Queue に投げることで処理されます。
Queue で実行している最中は本オブジェクトを破棄したり変更したりすることはできません。
一度記録した内容を再利用することも可能です。

コマンドの種類は大きく３つあります。

- Copy：後述のリソースをメモリコピーする機能。
- Render：レンダリングパイプラインを使ってレンダーターゲットに描画する機能。
- Compute：コンピュートパイプラインを使って演算する機能。

本オブジェクトは記録したコマンドの種類に対応している Queue に対して投げる必要があります。例えば Copy コマンドを記録した CommandBuffer は Copy コマンドに対応している Queue でないと登録できません。

## リソース・デスクリプタ

### ResourceMemory

### ImageResource

- SampledImageView
- StorageImageView
- RenderTargetImageView

### BufferResource

- UniformBufferView
- StorageBufferView
- IndirectBufferView

### ShaderModuleResource

### DesciptorSet

## Render 処理と関連するオブジェクト

### Render 処理について

Render 処理はレンダリングパイプラインは頂点を流し込みフレームバッファに描画する処理のことです。
基本的な処理の流れとしては以下の通りです。

1. RenderPass を使って描画先を設定。
2. Viewport や Scissor を設定。
3. RenderPipeline を使ってパイプラインを設定。
4. 設定されたパイプラインに必要なリソースを設定。
5. CmdDraw などの関数で描画をキック。

### RenderPass

### RenderPipeline

### SwapchainMaster・Swapchain


## Compute 処理と関連するオブジェクト

### Compute 処理について

### ComputePipeline

## Copy 処理

Copy 処理では Image リソースや Buffer リソースのコピーを行います。
例えば、グラフィックボードに搭載されている VRAM は CPU から直接メモリを書き換えたり読み取ったりすることができません。
VRAM と CPU 間でデータをやりとりするときなどにこの Copy 処理を使います。

Copy 処理は CommandBuffer の以下の関数を使ってコマンドを生成します。

- CndCopyBufferToImage
- CndCopyBuffer
