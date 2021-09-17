# Adel Engine Low Graphics Api Overview

## はじめに

このマニュアルでは ae::gfx_low モジュールについての概要を記述します。クラスや関数のリファレンスについては記述しません。

このマニュアルはグラフィックス API を使ったプログラミングの経験者の人が理解できるレベルの内容を想定しています。
もしそういった経験がない人はまず DirectX や Vulkan などで基本を抑えることをオススメします。

また、実際のコードの書き方は各サンプルを見てください。

## ae::gfx_low について

ae::gfx_low は低レベルグラフィックスライブラリをラップする API 郡で、Vulkan、DirectX12、Metal に対しての抽象化を実現する思想で作られています。

API 自体は抽象化を想定して設計されていますが、現在は Vulkan に対してのみ実装されています。

また、便利機能は基本的に用意していません。そのためユーザー側で必要に応じて用意してください。

## 基本的なオブジェクト

ae::gfx_low を使う上でまず以下のオブジェクトを作ることになります。

### System

System は何よりも先に作る必要があるオブジェクトです。
１実行アプリケーションにつき１つ作成してください。

### Device

Device は１つの GPU デバイスに対応するオブジェクトです。
普通の使い方ですと１つだけ作れば OK です。
本オブジェクトを通して GPU デバイスの情報を取得したりグラフィックスに関連するメモリの確保・解放を行ったりします。
本オブジェクトを作成する際に、後述の Queue も一緒に作成されます。

### Queue

Queue は GPU に対する命令コマンドを流し込む際に使うオブジェクトです。
後述の CommandBuffer を本オブジェクトに渡すことで GPU で処理されます。
最低１つ作成し、非同期コンピュートなどをする場合は必要に応じて２つ以上作成します。

### CommandBuffer

CommandBuffer は GPU に投げるコマンド（＝処理）を書き込むバッファです。
書き込まれたバッファは本オブジェクトを Queue に投げることで処理されます。
Queue で実行している最中は本オブジェクトを破棄したり変更したりすることはできません。
一度記録した内容を再利用することも可能です。

コマンドの種類は大きく３つあります。

- Copy：後述のリソースをメモリコピーする機能。
- Render：レンダリングパイプラインを使ってレンダーターゲットに描画する機能。
- Compute：コンピュートパイプラインを使って演算する機能。

本オブジェクトは記録したコマンドの種類に対応している Queue に対して投げる必要があります。例えば Copy コマンドを記録した CommandBuffer は Copy コマンドに対応している Queue でないと登録できません。

### Event

### Fence

## リソース・デスクリプタ

リソースとは GPU が参照する各種データのことです。
リソースには以下の３種類が存在します。

- ImageResource：画像データを扱うリソース
- BufferResource：非画像データ全般を扱うリソース
- ShaderResource：シェーダーデータを扱うリソース

また、各リソースを GPU のレジスタに設定するものをデスクリプタと呼びます。
例えば１つの ImageResource につき SampledImageView というデスクリプタを用意する、といった感じです。
デスクリプタは何種類もありますが、それについては各リソースの説明の際に紹介します。

### ResourceMemory

Device から確保したリソースのメモリ領域を扱うオブジェクトです。
メモリを確保する際はメモリサイズはもちろん、そのメモリ領域がどのような用途で使われるかも指定して確保します。

また、ResourceMemory を Map/Unmap することでメモリの内容を CPU 上から読み書きすることができます。

### UniqueResourceMemory

ae::gfx_low の中で唯一の便利クラスです。
std::unique_ptr と同じように ResourceMemory の確保と解放を管理します。

### ImageResource

ImageResource は画像リソースを扱うオブジェクトです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

ImageResource に関するデスクリプタ類は以下の通りです。

- SampledImageView：画像データリード用のデスクリプタ
- StorageImageView：画像データライト用のデスクリプタ
- RenderTargetImageView：Render 処理の描画先用デスクリプタ

### Sampler

Sampler は SampledImageView に対してどのように画像データをリードするかを定義したデスクリプタです。
例えば、ミップマップを使うか、線形補間をするか、といった設定を定義します。
SampledImageView を使う場合は Sampler が必ず必要になります。
Sampler はデスクリプタの中で唯一 ResourceMemory が不要なデスクリプタです。

### BufferResource

BufferResource は画像ではないデータを扱うオブジェクトです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

BufferResource に関するデスクリプタ類は以下の通りです。

- UniformBufferView：データリード用のデスクリプタ
- StorageBufferView：データライト用のデスクリプタ
- VertexBufferView：頂点バッファを指定する用のデスクリプタ
- IndexBufferView：インデックスバッファを指定する用のデスクリプタ
- IndirectBufferView：インダイレクト描画用のデスクリプタ

### ShaderModuleResource

ShaderModuleResource はシェーダーリソースを扱うモジュールです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

シェーダーリソースとして設定するデータは使用するグラフィックス API 毎に変わります。
Vulkan 環境ですと SPiR-V 形式のバイナリファイルを使用します。

### DesciptorSet

DescriptorSet は複数のデスクリプタを１つにまとめたオブジェクトです。
DescriptorSet を CommandBuffer に設定することで GPU のレジスタに各デスクリプタが設定されます。

VertexBufferView や IndexBufferView など一部デスクリプタは DescriptorSet を使わずに設定します。

シェーダーバインディングにはルールを設けています。詳しくは DescriptorSetSpecInfo のクラスコメントを参照してください。

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

### インダイレクト描画

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
