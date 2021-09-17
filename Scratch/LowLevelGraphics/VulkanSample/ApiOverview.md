# AdelEngine GfxLowApi Overview

<!-- TOC -->

- [AdelEngine GfxLowApi Overview](#adelengine-gfxlowapi-overview)
  - [はじめに](#はじめに)
  - [ae::gfx_low について](#aegfx_low-について)
  - [基本的なオブジェクト](#基本的なオブジェクト)
    - [System](#system)
    - [Device](#device)
    - [Queue](#queue)
    - [CommandBuffer](#commandbuffer)
  - [同期](#同期)
    - [Event](#event)
    - [Fence](#fence)
  - [リソース・デスクリプタ](#リソース・デスクリプタ)
    - [ResourceMemory](#resourcememory)
    - [UniqueResourceMemory](#uniqueresourcememory)
    - [BufferResource](#bufferresource)
    - [ImageResource](#imageresource)
    - [Sampler](#sampler)
    - [ShaderModuleResource](#shadermoduleresource)
    - [DesciptorSet](#desciptorset)
  - [Render 処理と関連するオブジェクト](#render-処理と関連するオブジェクト)
    - [Render 処理について](#render-処理について)
    - [RenderPass](#renderpass)
    - [Viewport・Scissor](#viewport・scissor)
    - [RenderPipeline](#renderpipeline)
    - [デスクリプタ設定](#デスクリプタ設定)
    - [描画コール](#描画コール)
    - [インダイレクト描画](#インダイレクト描画)
    - [SwapchainMaster・Swapchain](#swapchainmaster・swapchain)
  - [Compute 処理](#compute-処理)
  - [Copy 処理](#copy-処理)

<!-- /TOC -->

## はじめに

このマニュアルでは ae::gfx_low モジュールについての概要を記述します。

このマニュアルはグラフィックス API を使ったプログラミングの経験者が本モジュールの概要を把握できることを目指して書いています。
もしそういった経験がない人はまず DirectX や Vulkan などで基本を抑えることをオススメします。

このマニュアルにはクラスや関数のリファレンスについては記述しません。API の詳細や使い方はソースコードや各サンプルで確認してください。

## ae::gfx_low について

ae::gfx_low は低レベルグラフィックスライブラリをラップする API 郡で、Vulkan、DirectX12、Metal やプライベートなグラフィックス API に対しての抽象化を実現する目的で作られています。

API 自体は抽象化を想定して設計されていますが、現在は Vulkan に対してのみ実装されています。

また、便利機能は基本的に用意していません。そのためユーザー側で必要に応じて用意してください。

## 基本的なオブジェクト

ae::gfx_low を使う上でまず以下のオブジェクトを作ります。

### System

System は何よりも先に作る必要があるオブジェクトです。
１実行アプリケーションにつき１つ作成してください。

### Device

Device は１つの GPU デバイスに対応するオブジェクトです。
普通の使い方ですと１実行アプリケーションにつき１つだけ作成することになります。
Device オブジェクトを通して GPU デバイスの情報を取得したりグラフィックスに関連するメモリの確保・解放を行ったりします。
Device を作成する際に、後述の Queue も一緒に作成されます。

### Queue

Queue は CPU から GPU にコマンドや命令を送信する際に使うオブジェクトです。
後述の CommandBuffer を本オブジェクトに渡すことでコマンドが GPU で処理されます。
最低１つ作成し、非同期コンピュートなどをする場合は必要に応じて２つ以上作成します。

### CommandBuffer

CommandBuffer は GPU に送信するコマンド（＝処理）を書き込むバッファです。
書き込まれたバッファは本オブジェクトを Queue に登録することで処理されます。
Queue で実行している最中は本オブジェクトを破棄したり変更したりすることはできません。

一度記録した内容を再利用することも可能です。

コマンドの種類は大きく３つあります。

- Copy：リソース間でメモリコピーする機能。
- Render：レンダリングパイプラインを使ってレンダーターゲットに描画する機能。
- Compute：コンピュートパイプラインを使って演算する機能。

CommandBuffer は記録したコマンドの種類に対応している Queue に対してのみ登録することができます。例えば Copy コマンドを記録した CommandBuffer は Copy コマンドに対応している Queue でないと登録できません。

CommandBuffer にコマンドを詰む関数は全て頭に `Cmd` という接頭辞がついています。このマニュアルでも CmdXxxx といった単語が何回も登場しますが、それは全て CommandBuffer にコマンドを詰む関数になります。

CommandBuffer の基本的な使い方は CommandBuffer のクラスコメントを参照してください。

CommandBuffer から別の CommandBuffer をコールすることも可能です。
CommandBuffer から呼び出せる CommandBuffer は CommandBufferLevel::Secondary で生成したセカンダリコマンドバッファのみです。
セカンダリコマンドバッファにはいくつかの制約があります。詳しくは CommandBuffer のクラスコメントを参照してください。

## 同期

同期用オブジェクトとして Event と Fence が用意されています。

### Event

Event は複数の Queue 間でタイミングを同期する際に使うオブジェクトです。
例えば非同期コンピュートの処理が終わってからレンダリング処理を開始したい、といったときに使います。

### Fence

Fence は Queue が特定のコマンドまで処理できたタイミングを CPU 上で同期する際に使うオブジェクトです。
例えば GPU の処理が終わったことを確認してから CPU 上でメモリをリード/ライトする、といったときに使います。

## リソース・デスクリプタ

リソースとは GPU が参照する各種データのことです。
リソースには以下の３種類が存在します。

- BufferResource：非画像データ全般を扱うリソース
- ImageResource：画像データを扱うリソース
- ShaderResource：シェーダーデータを扱うリソース

また、各リソースを GPU のレジスタに設定するものをデスクリプタと呼びます。
例えば１つの ImageResource につき SampledImageView というデスクリプタを用意し、DescriptorSet を使って GPU のレジスタにデスクリプタを設定をする、といった感じです。
デスクリプタは何種類もありますが、それについては各リソースの説明の際に紹介します。

### ResourceMemory

ResourceMemory は Device から確保したリソースのメモリ領域を扱うオブジェクトです。
メモリを確保する際はメモリサイズはもちろん、そのメモリ領域がどのような用途で使われるか、つまり使用用途も指定して確保します。

使用用途は ResourceMemoryUsage に列挙されていて、例えば読み込みイメージ用のメモリとして使う場合は SampledImage を指定する必要があります。使用用途によってメモリサイズの繰り上げや必要になったり要求されるアライメントが異なりますが、それらの情報は Device から取得できます。

また、ResourceMemory を Map/Unmap することでメモリの内容を CPU 上から読み書きすることができます。

### UniqueResourceMemory

ae::gfx_low の中で唯一の便利クラスです。
std::unique_ptr と同じように ResourceMemory の自動解放を管理します。

### BufferResource

BufferResource は画像ではないデータを扱うオブジェクトです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

BufferResource に関するデスクリプタ類は以下の通りです。

- UniformBufferView：データリード用のデスクリプタ
- StorageBufferView：データライト用のデスクリプタ
- VertexBufferView：頂点バッファ指定用のデスクリプタ
- IndexBufferView：インデックスバッファ指定用のデスクリプタ
- IndirectBufferView：インダイレクト描画用のデスクリプタ

### ImageResource

ImageResource は画像リソースを扱うオブジェクトです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

ImageResource に関するデスクリプタ類は以下の通りです。

- SampledImageView：画像データリード用のデスクリプタ
- StorageImageView：画像データライト用のデスクリプタ
- RenderTargetImageView：Render 処理のレンダーターゲット用デスクリプタ

ImageResource には ImageResourceState というメモリバリアの概念があります。例えば、RenderTargetImageView として使用していたイメージを SampledImageView として使いたい場合は ImageResourceState を RenderTarget から ShaderResourceReadOnly に状態遷移させる必要があります。

### Sampler

Sampler は SampledImageView に対してどのように画像データをリードするかを定義したデスクリプタです。
例えば、ミップマップを使うか、線形補間をするか、といった設定を定義します。
SampledImageView を使う場合は Sampler が必ず必要になります。
Sampler はデスクリプタの中で唯一 ResourceMemory が不要なデスクリプタです。

### ShaderModuleResource

ShaderModuleResource はシェーダーリソースを扱うモジュールです。
本オブジェクトは ResourceMemory の領域を指定することで作成できます。

シェーダーリソースとして設定するデータは使用するグラフィックス API によって変わります。
例えば Vulkan 環境では SPiR-V 形式のバイナリデータを使用します。

### DesciptorSet

DescriptorSet はシェーダーが参照する各デスクリプタへの参照を１つにまとめたオブジェクトです。
DescriptorSet を CommandBuffer に設定することで、DescriptorSet が参照する各デスクリプタが GPU のレジスタに設定＆シェーダーバインディングされます。そうすることでシェーダーは各デスクリプタが指すリソースを参照することができるようになります。

シェーダーバインディングにはルールを設けています。詳しくは DescriptorSetSpecInfo のクラスコメントを参照してください。

なお、VertexBufferView や IndexBufferView などシェーダーではなくパイプラインが参照するデスクリプタは DescriptorSet は使わずパイプライン設定後に CommandBuffer に直接設定します。詳しくは後述の Render 処理や Compute 処理の項を参照してください。

## Render 処理と関連するオブジェクト

### Render 処理について

Render 処理はレンダリングパイプラインに頂点を流し込み、シェーダーによってレンダーターゲットに描画する処理のことです。
基本的な処理の流れとしては以下の通りです。

1. CmdBeginRenderPass でレンダー処理の開始を宣言。
2. Viewport や Scissor を設定。
3. RenderPipeline を使ってパイプラインを設定。
4. 設定されたパイプラインに必要なリソースをデスクリプタを使って設定。
5. 描画コール。
6. CmdEndRenderPass でレンダー処理の終了を宣言。

この例では描画コール後にすぐにレンダー処理の終了を宣言していますが、他にも同じレンダーパス設定で描画するものがある場合は終了宣言の前に追加で３〜５番の処理を行って下さい。

### RenderPass

RenderPass はレンダーターゲットやカラーバッファやデプスバッファのクリア処理等の設定を行います。

RenderPass は CmdBeginRenderPass/CmdEndRenderPass を使って開始終了処理を行います。

### Viewport・Scissor

ビューポートとシザーは CmdSetViewports/CmdSetScissors で設定します。

ビューポートとシザーは RenderPass 設定後に設定してください。

### RenderPipeline

RenderPipeline は描画パイプラインに関する設定を保持するオブジェクトです。
例えば、デプステスト設定、ブレンドテスト設定、面カリング設定、シェーダーモジュールの設定、頂点バッファのレイアウト、デスクリプタの構成、レンダーターゲットの構成（カラーバッファの枚数や各カラーバッファのフォーマット等）、他、こういった情報が RenderPipeline に含まれます。

RenderPipeline は描画パイプラインの設定毎に１つのオブジェクトを作る必要があります。１つでも設定が異なる場合は別の RenderPipeline オブジェクトを作って下さい。

RenderPipeline は CmdSetRenderPipeline を使って設定します。

### デスクリプタ設定

デスクリプタは RenderPipeline を設定した後に以下の関数で設定してください。

- CmdSetDescriptorSet
- CmdSetVertexBuffer
- CmdSetIndexBuffer

### 描画コール

デスクリプタ設定までできたら描画コールを行います。

描画コールは以下の関数で行って下さい。

- CmdDraw
- CmdDrawIndirect

IndexBuffer を使うかどうかは関数の引数に渡す DrawCallInfo/DrawIndrectCallInfo で指定してください。

### インダイレクト描画

CmdDrawIndirect で描画コールすることでインダイレクト描画ができます。

インダイレクト描画のコマンド引数は IndirectBufferView で指定します。

インダイレクト描画のコマンド引数のデータを CPU 上で生成する場合は DrawIndirectNormalCommand/DrawIndirectIndexedCommand にキャストして設定してください。

### SwapchainMaster・Swapchain

描画結果をディスプレイに表示する場合は Swapchain に最終画像を提出する必要があります。

Swapchain は SwapchainMaster 経由で取得できます。

描画結果をディスプレイに表示するには Swapchain の持つ RenderTargetView に対して描画を行った後、Queue::Present をしてください。

SwapchainMaster は現在ディスプレイに表示されていない Swapchain も保持しています。例えばトリプルバッファをする場合は３つの Swapchain を保持しています。

## Compute 処理

Compute 処理は GPGPU の機能を使って GPU 上で実行する計算処理のことです。

Compute 処理は以下の流れで行います。

1. CmdBeginComputePass を使って Compute 処理の開始を宣言。
2. CmdSetComputePipeline を使ってパイプラインを設定。
3. CmdSetDescriptorSet を使ってデスクリプタを設定。
4. CmdDispatch を使って Compute 処理を開始。
5. 最後に CmdEndComputePasss を使って Compute 処理の終了を宣言。

Render 処理と同様に、同じ ComputePass で複数の Compute 処理をしたい場合は２〜４番の処理を必要に応じて追加してください。

Compute した結果を CPU や GPU で参照する場合は同期オブジェクトや ImageResourceState などのバリアを使って同期を取ってから参照してください。

## Copy 処理

Copy 処理では Image リソースや Buffer リソースのコピーを行います。
例えば、グラフィックボードに搭載されている VRAM は CPU から直接メモリを書き換えたり読み取ったりすることができません。そういった環境で VRAM とメモリ間でデータをやりとりするときにこの Copy 処理を使います。

Copy 処理は CommandBuffer の以下の関数を使ってコマンドを生成します。

- CmdCopyBufferToImage
- CmdCopyBuffer
