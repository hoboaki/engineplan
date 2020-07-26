# 3D グラフィックス低レベル API に関するメモ

この資料はクロスプラットフォームな 3D グラフィックスライブラリを検討する個人的な資料です。各グラフィックスライブラリの差異をまとめたり，クロスプラットフォームなライブラリの設計や最適化に関するメモを書き残します。

<!-- TOC -->

- [3D グラフィックス低レベル API に関するメモ](#3d-グラフィックス低レベル-api-に関するメモ)
- [オブジェクト](#オブジェクト)
  - [キュー・コマンドバッファ生成](#キュー・コマンドバッファ生成)
    - [Vulkan](#vulkan)
    - [DirectX 12](#directx-12)
    - [Metal](#metal)
  - [スワップチェイン生成](#スワップチェイン生成)
    - [Vulkan](#vulkan-1)
    - [DirectX 12](#directx-12-1)
    - [Metal](#metal-1)
  - [バッファ生成・リソースオブジェクト](#バッファ生成・リソースオブジェクト)
    - [Vulkan](#vulkan-2)
    - [DirectX 12](#directx-12-2)
    - [Metal](#metal-2)
  - [シェーダーオブジェクト生成](#シェーダーオブジェクト生成)
    - [Vulkan](#vulkan-3)
    - [DirectX 12](#directx-12-3)
    - [Metal](#metal-3)
  - [サンプラ生成](#サンプラ生成)
    - [Vulkan](#vulkan-4)
    - [DirectX 12](#directx-12-4)
    - [Metal](#metal-4)
  - [デスクリプタ・デスクリプタプール](#デスクリプタ・デスクリプタプール)
    - [Vulkan](#vulkan-5)
    - [DirectX 12](#directx-12-5)
    - [Metal](#metal-5)
- [コマンド・フロー](#コマンド・フロー)
  - [レンダターゲット](#レンダターゲット)
    - [Vulkan](#vulkan-6)
    - [DirectX 12](#directx-12-6)
    - [Metal](#metal-6)
  - [スワップチェイン提出（present）＆同期](#スワップチェイン提出present＆同期)
    - [Vulkan](#vulkan-7)
    - [DirectX 12](#directx-12-7)
    - [Metal](#metal-7)
  - [コマンドバッファで設定する単位](#コマンドバッファで設定する単位)
    - [Vulkan](#vulkan-8)
    - [DirectX 12（コマンドリスト）](#directx-12コマンドリスト)
    - [Metal（コマンドエンコーダ）](#metalコマンドエンコーダ)
  - [キューの並列実行](#キューの並列実行)
    - [Vulkan](#vulkan-9)
    - [DirectX 12](#directx-12-8)
    - [Metal](#metal-8)
  - [キュー間同期](#キュー間同期)
    - [Vulkan](#vulkan-10)
    - [DirectX 12](#directx-12-9)
    - [Metal](#metal-9)
  - [メモリバリア](#メモリバリア)
    - [Vulkan](#vulkan-11)
    - [DirectX 12](#directx-12-10)
    - [Metal](#metal-10)
  - [CPUGPU 間同期](#cpugpu-間同期)
    - [Vulkan](#vulkan-12)
    - [DirectX 12](#directx-12-11)
    - [Metal](#metal-11)
- [最適化](#最適化)
  - [セカンダリコマンドバッファ](#セカンダリコマンドバッファ)
    - [Vulkan](#vulkan-13)
    - [DirectX 12](#directx-12-12)
    - [Metal](#metal-12)
  - [インダイレクト引数描画](#インダイレクト引数描画)
    - [Vulkan](#vulkan-14)
    - [DirectX 12](#directx-12-13)
    - [Metal](#metal-13)
  - [バッファ生成時初期値指定](#バッファ生成時初期値指定)
- [付録](#付録)
  - [参考](#参考)

<!-- /TOC -->

# オブジェクト

## キュー・コマンドバッファ生成

- キューについて
  - 特性指定生成は DX12 形式で統一するとシンプルでよさそう。
  - Vulkan みたいに細かく指定する方法もあるが，実際メイン，Compute，Copy の３種があればやりたいことはだいたいできる。
  - Vulkan にあわせるとキューの生成は Device 作成時に指定せざるえなくなる。
  - それですごい不便とは思わないのでその形式であわせよう。
- コマンドバッファの抽象化設計
  - 生成の引数に所属する Queue を指定。そうすると３ライブラリ汎用化可能。
  - Primary の特性は１つに限定せず汎用的なコマンドバッファとする。
  - Metal では beginRenderPass/ComputePass endRenderPass/ComputePass のタイミングで CommandEncoder を作りなおして切り替える。
  - Secondary Metal の IndirectCommandBuffer を考慮して Render と Compute のどちらか１種のみサポートする。
- コマンドバッファ生成時の最大コマンド数指定について
  - Metal のセカンダリでは必須なので入力の口は用意する。

### Vulkan

- Queue は Device 作成時に引数オブジェクトで指定。
- Queue の特性は QueueFamily というビットフラグセットで構成され，最終的には QueueFamilyIndex で指定する。
- コマンドバッファの生成の前に CommandPool の生成が必要。
- CommandPool 生成時にバッファは求められない。指定する方法も見当たらない。
- CommandPool は生成時に QueueFamilyIndex を要求される。Queue 毎に作るものと考えると設計は簡単。
- CommandPool で扱える最大コマンド数の指定も見当たらない。無限大なわけではないのでそこは気になる。
- CommandBuffer 生成時に CommandPool を渡す。

### DirectX 12

- Queue は Direct，コンピュート専用，コピー専用と別れているっぽい。（ソースは[こちら](https://sites.google.com/site/monshonosuana/directxno-hanashi-1/directx-143)）
- Direct はコンピュートもコピーもできるらしい。
- 他のライブラリで見られるようなビットフラグで複数の特性を指定して作成，という感じではない。
- コマンドバッファに相当する CommandList には CommandAllocator が必要。
- CommandList も CommandAllocator も最大コマンド数といったものやバッファを指定する口はない。Vulkan と同様。
- CommandList と CommandAllocator は D3D12_COMMAND_LIST_TYPE を合わせる必要があり。
- CommandList 作成時に CommandAllocator を渡す。
- D3D12_COMMAND_LIST_TYPE は Direct，Bundle（セカンダリコマンドバッファ），Compute，Copy といったものがある。
- Direct は Queue の Direct と同じく色々できる特性。
- 裏取りしていないが Queue が Compute や Copy のものは CommandList と CommandAllocator もあわせる必要があるのではと予想。
- Queue が Direct の場合はキューの特性が汎用と考えると Compute と Copy もいけるかも？要裏取り。

### Metal

- Queue は Device.makeCommandQueue で作成。
- Queue 作成時に最大コマンドバッファ数を指定するものと指定しないものがある。
- 違いについて言及されていないがたぶん数を指定すると多少パフォーマンスがよくなるんでしょう。
- Queue は特性を指定する方法はない。
- CommandBuffer は Queue.makeCommandBuffer で作成。
- 引数あり版では参照安全の仕組みを切るオプションがあり，厳密にオブジェクトの寿命管理できるんだったら切っておいたほうがパフォーマンスが上がる模様。
- CommandBuffer のレベルでも特性はない。
- CommandBuffer に対して Render, Compute, Blit それぞれの CommandEncoder を作成する。そこでようやく特性を意識することになる。
- CommandBuffer にバッファを指定する口はない。
- セカンダリコマンドバッファは [Device.makeIndirectCommandBuffer](https://developer.apple.com/documentation/metal/indirect_command_buffers/creating_an_indirect_command_buffer) で作成。
- こちらは maxCount で最大コマンド数の指定が必須。
- どうやら Encoder を使うのではなく、インデックスで取得した Command オブジェクト１つ１つに対して set していくっぽい。
- そして呼び出しは Render なら RenderCommandEncoder の executeCommandsInBuffer で行うらしい。

## スワップチェイン生成

- あらかじめバッファ確保パターンに対応させたい
  - この３ライブラリではできないが，あらかじめ確保していたバッファを使って作れるようにもしておきたい。
  - その狙いも込めて，SwapchainManager みたいなものを用意してそれ経由で Swapchain を作るようにするようにする。
- 抽象化設計
  - Metal のことを考えると全レンダーターゲットイメージを取得する方法を提供できない。
  - 抽象化するなら Image オブジェクト，イメージビュー，レンダーターゲットビューをスワップチェイン側で作るしかない。
  - これら３種のオブジェクトは acquire() したら現在提出対象のスワップチェインに付随するものを取得できるようにする，がよさそう。

### Vulkan

- プラットフォーム非依存の作成関数は[こちら](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCreateSwapchainKHR.html)。
- 指定するものはサイズ，イメージフォーマットと枚数。あとは細々とオプションが，という印象。
- デバイスロストしたときは再生成が必要。
- [vkAcquireNextImageKHR](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkAcquireNextImageKHR.html)呼び出しでインデックスを取得。
- レンダーターゲット用の VkImageView は別途作成が必要。

### DirectX 12

- Windows 用の作成関数は[こちら](https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd)。
- 指定するものはサイズ，イメージフォーマットと枚数。あとは細々とオプションが，という印象。
- それに加えて所属する CommandQueue を渡すのが独特。
- [GetCurrentBackBufferIndex()](https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgiswapchain3-getcurrentbackbufferindex) でインデックス取得。
- レンダーターゲット用の ImageView は別途作成が必要。

### Metal

- Swapchain という名前のものはなく，あえて挙げるなら[CAMetalLayer](https://developer.apple.com/documentation/quartzcore/cametallayer)。
- [nextDrawable()](https://developer.apple.com/documentation/quartzcore/cametallayer/1478172-nextdrawable) でフレームバッファテクスチャを取得できる。

## バッファ生成・リソースオブジェクト

- はじめに
  - GPU がアクセスするありとあらゆるバッファが各 API でどう扱われているか。
  - 想定されるバッファは以下の通り。
    - イメージ
    - 頂点
    - インデックス
    - コンスタント
    - ストレージ（UAV）
    - インダイレクト描画引数
    - シェーダーバイナリ
    - コマンドバッファ
    - デスクリプタ
- シェーダーバイナリ・コマンドバッファ・デスクリプタ
  - 全ライブラリともにシェーダーバイナリ，コマンドバッファ，デスクリプタはバッファでは扱わない模様。
  - これらのメモリ領域をバッファで扱うタイプのライブラリのことも考慮しておきたい。
  - コマンドバッファとデスクリプタはランタイムで生成するものだから特別扱いしなくても良いとして問題はシェーダーバイナリ。
  - シェーダーバイナリは頂点やインデックスと同様にファイルから読み込んできてそのままバッファ内に配置して使うケースもある。
  - シェーダーオブジェクト生成について調べたが，Vulkan DX12 Metal すべてバイナリ指定可能。
  - となると，抽象化ライブラリではシェーダーリソースはバッファで渡すようにしておくとよさそう。
  - その際，バッファの特性にシェーダーバイナリを指定させる。
- 抽象化
  - リソースオブジェクトは Image と Buffer の２種あると全ライブラリカバーできる。
  - リソースっぽいのが分かるように ImageResource と BufferResource と名付ける。
  - リソースオブジェクトに割り当てるメモリは ResourceHeap・ResourceMemory 的な名前で扱う。

### Vulkan

- VkDeviceMemory がバッファ。メモリ領域のハンドル。
- バッファ特性（Map 可能不可能・メモリ配置場所など）を指定して vkAllocateMemory で確保する。
- あらかじめ大きい領域を確保しておいてそれを分けて使う，というのは可能。
- ユーザー側の指定した領域を割り当てたい場合は vkAllocateMemory に渡すコールバックオブジェクトで割り当てたいポインタを返す。
- リソースオブジェクトとしては VkImage と VkBuffer の２種類。前者はテクスチャ系用，後者はそれ以外。
- vkBindImageMemory vkBindBufferMemory でバッファを割り当てる。offset 指定も可能。
- シェーダーオブジェクト，コマンドバッファ，デスクリプタはバッファでは扱わない。

### DirectX 12

- バッファとしては Heap として表現される。大きい Heap を作って細かく分割して使うことは可能。
- Heap 作成時にバッファ特性を指定する。
- ユーザー側の指定した領域を割り当てる方法はなさそう。
- バッファ領域を特定のリソースとして定義するのは Resource (ID3DResource) オブジェクト。
- Resource はメモリ領域とテクスチャなら Width，Height, Format などの情報を持つ。
- 更にその Resource を GPU が扱えるようにするために View がでてくる。
- View はデスクリプタの扱いになるのでこの項では扱わない。
- ちなみに頂点バッファとインデックスバッファは View と名の付くオブジェクトはあるがデスクリプタ扱いではなく単なる構造体。
- シェーダーオブジェクト，コマンドバッファ，デスクリプタはバッファでは扱わない。

### Metal

- MTLHeap でバッファ領域を確保。
- Device.makeHeap で作成可能。引数でバッファ特性を指定。
- MTLHeap.makeBuffer や MTLHeap.makeTexture で MTLBuffer MTLTexture を作成。どちらも MTLResource と呼ばれるもの
- View （＝デスクリプタ）の概念はないので，コマンドバッファにはこれら MTLResource をそのまま設定。
- シェーダーオブジェクト，コマンドバッファはバッファでは扱わない。

## シェーダーオブジェクト生成

- 実行時コンパイルをサポートしているライブラリもあるが基本はランタイムコンパイルはサポートしない，にしておけば抽象化は簡単になる。
- Metal には頂点属性といった付加情報もセットでシェーダーバイナリに含まれているが他２種にはないので採用しない。

### Vulkan

- VkShaderModule がシェーダーオブジェクト。
- vkCreateShaderModule で作成。引数には SPIR-V バイナリを指定。
- シェーダのリソースはバッファでは扱わないし，SPIR-V から GPU で扱う用に変換されたバイナリ領域を取得する手段もない。
- 特定コンソール専用バイナリシェーダーを流しこむ場合は pCode に専用バイナリを流せるようにするのかなと想像。
- SPIR-V バイナリへのコンパイルは SDK 付属のコマンドラインアプリで可能。

### DirectX 12

- バイナリの塊がシェーダーオブジェクト。何かの型で扱うということはない。
- dxc.exe でコンパイル可能。

### Metal

- MTLFunction がシェーダーオブジェクト。
- 頂点属性といった付加情報も MTLFunction から取得できる。これは他２種のライブラリにはない機能。
- MTLFunction.makeArgumentEncoder を用いて ArgumentBuffer （デスクリプタセット）が作成できる。
- MTLFunction は MTLLibrary から取得可能。
- 事前コンパイル済データを MTLDevice.makeLibrary() にかませば MTLLibrary が作れる。ソースコードを渡せるオーバーロードもある。
- コマンドラインツールの説明は[こちら](https://developer.apple.com/library/archive/documentation/Miscellaneous/Conceptual/MetalProgrammingGuide/Dev-Technique/Dev-Technique.html#//apple_ref/doc/uid/TP40014221-CH8-SW8)。

## サンプラ生成

- 基本構成はすべて同じ。なのでその形式を継承する。
- DirectX 12 だけ作成手続きすら不要だが，他２種にあわせて作成手続きは用意する。

### Vulkan

- VkSampler vkCreateSampler() で作成。
- DescriptorSet に設定する。

### DirectX 12

- D3D12_STATIC_SAMPLER_DESC で表現。ただのデータ構造で作成の必要もない。
- RootSignature に設定する。

### Metal

- MTLSamplerState で表現。MTLDevice.makeSamplerState() で作成。
- ArgumentEncoder などの Encoder.setSamplerState で設定。

## デスクリプタ・デスクリプタプール

- Vulkan がデスクリプタプールはトリガー時に１つしか使えず一番制約がきつい。
- なのでそれにあわせておけば抽象化は簡単。
- 注意点として DirectX 12 のみ RenderTargetView DepthStencilView という概念が必要。
- なので，抽象化時も ImageView だけでなくその２つも用意しておくとよさそう。Vulkan では無駄になっちゃうけど。

### Vulkan

- VkDescriptorPool がデスクリプタプール。
- VkDescriptorSet とデスクリプタの最大数を引数で指定して VkDescriptorPool を作成。
- VkDescriptorPool の抱えるメモリ領域は VkAllocationCallbacks でカスタマイズは可能。
- １つの DescriptorPool に複数タイプのデスクリプタを作成することが可能。タイプについては[こちら](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkDescriptorType.html)。
- VkDescriptorSet を作るときは１つの VkDescriptorPool しか指定できない。
- VkDescriptorSet を更新するのは vkUpdateDescriptorSets で。
- VkDescriptorSet は vkCmdBindDescriptorSets でコマンドバッファに設定。その際 vkPipeline オブジェクトも要求される。

### DirectX 12

- ID3D12DescriptorHeap がデスクリプタプール。
- 最大デスクリプタ数やタイプなどを引数指定して ID3D12Device.CreateDescriptorHeap() で作成。
- ID3D12DescriptorHeap は１つに１つき１タイプを扱う。タイプについては[こちら](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_descriptor_heap_type)。
- ID3D12DescriptorHeap が抱えるメモリ領域を指定できる手段はない。
- ID3D12GraphicsCommandList.SetDescriptorHeaps で使用する ID3D12DescriptorHeap を複数設定。
- デスクリプタの設定は ID3D12GraphicsCommandList.SetGraphicsRootDescriptorTable で。

### Metal

- デスクリプタの概念がなく，コマンドバッファ（CommandEncoder）に setBuffer やら setTexture していく。

# コマンド・フロー

## レンダターゲット

- Vulkan のことも考慮して FrameBufferSet 的なオブジェクトで指定できるようにする。
- イメージビューではなくレンダーターゲットビュー＆デプスステンシルビューで設定。
- パイプライン設定でレンダーターゲット構成を宣言しないといけないので，構成は FrameBufferSetLayout 的なもので定義。

```yml
# クラス設計

# 仕様（パイプラインでも求められるもの）
RenderPassSpec
- RenderTargetSpec[]
- DepthStencilSpec

# BeginRenderPass に渡す情報
RenderPass
- RenderPassLayout
- RenderTargetSetting[]
  - RenderTargetImageView
  - InitialImageResourceState
  - FinalImageResourceState
  - ClearSetting
- DepthStencilSetting
  - DepthStencilImageView
  - InitialImageResourceState
  - FinalImageResourceState
  - ClearSetting
``` 

### Vulkan

- [vkFrameBuffer](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkFramebuffer.html) オブジェクトで表現。名前だけみると１枚のレンダーターゲットしか扱えなさそうに見えるけど違う。
- [vkCreateFrameBuffer](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCreateFramebuffer.html)で作成。毎フレーム作るのはやめておいたほうがよさそう。
- 設定は RenderPassBegin 時に指定。

### DirectX 12

- RenderTargetView と DepthStencilView が必要。どちらもデスクリプタ。
- 他２種のライブラリは Image もしくは ImageView という読み取り時と同じオブジェクトで表現しているが，DirectX 12 は専用となる。
- [CreateRenderTargetView()](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12device-createrendertargetview) や [CreateDepthStencilView()](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12device-createdepthstencilview) で作成。
- コマンドリストに対して OMSetRenderTargets でデスクリプタ配列で指定。

### Metal

- RenderCommandEncoder 作成時に指定。
- MTLTexture オブジェクトをそのまま設定。

## スワップチェイン提出（present）＆同期

- キューに対して提出するのがよさそう。
- 引数で SwapChain オブジェクトを渡しておけば DirectX 12 がカバーできる。
- Present 予約が完了したかどうかを判定したい場合は CPU&GPU 間同期のフェンスを使う。
- Present 完了を検出する方法は用意しない。

### Vulkan

- [vkQueuePresentKHR()](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkQueuePresentKHR.html) で present 処理する。引数は vkQueue と同期用（前処理終了検知用）の vkSemaphore が求められる。
- この関数は Present 予約するコマンドを積むだけでブロックはしない。
- Present 予約に対する同期する方法はない。 https://github.com/KhronosGroup/Vulkan-Docs/issues/370
- [VK_PRESENT_MODE_FIFO_KHR](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPresentModeKHR.html) をみる限り、垂直同期をしつつつ Present 予約済の Swapchain の Present 完了処理をしていく。
- Swapchain バッファが使っていい状態になっているかどうかは [vkAcquireNextImageKHR](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkAcquireNextImageKHR.html) の引数で渡す semaphore もしくは fence にシグナルが来ているかどうかで判定するらしい。

### DirectX 12

- [IDXGISwapChain.Present()](https://docs.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present) で present 処理をする。
- SwapChain 生成時に CommandQueue を渡しているので、おそらく内部でその Queue に対して preset 処理を入れていると推測できる。
- ~~呼び出しまでに GPU 側の処理が終わっていなければブロックするらしい。（ほんとに？）~~
- ~~終わっていたらノンブロック。おそらく画面フリップの予約だけしてあとは OS にお任せ，ということなのだろう。（ほんとに？）~~
- Present() は CommandQueue にコマンドをのせるだけなのですぐもどってくる。
- Present() の引数 SyncInterval で 1 を指定した場合、「過去に Present したイメージが少なくとも１フレ描画してから Present 予約を実行する」という意味と思われる。
- ということは SyncInterval に 1 を指定した場合、過去に Present したイメージが１フレ描画されるまでは CommandQueue が待っているのかな？
- 同期は CommandQueue に対する Fence & Event を使った CPU&GPU 間同期が可能。上記の理解で正しいのであれば Present 完了の同期ではなく Present 予約の同期だけ可能となる。
- ただ、 SyncInterval に 1 を指定し続ければバッファが２枚あれば上書きすることは防げると思われる。

### Metal

- MTLCommandBuffer.present() で present 処理する。
- 関数リファレンスには drawable に対する描画処理が完了次第できる限り早く present 処理をする、とある。
- MoltenVk のコード MVKPresentableSwapchainImage::presentCAMetalDrawable を見ると、present() したあとに CPU&GPU 同期できているように見える。
- ここでいう同期が present 処理が予約だけなのか完了までをさしているのかは不明。たぶん予約だけだと予想。

## コマンドバッファで設定する単位

- 抽象化の分け方は LowLevelGraphicsApi.numbers の表を参照。

### Vulkan

★ マークがあるところは他の箇所と値を一致させる必要あり。
★2 のレンダーパスについては互換があれば OK で完全一致である必要はない。互換があればオブジェクトとして別でも OK。（後述参照）

- RenderPassBegin（レンダーターゲットクリアのトリガーも担う）
  - レンダーパス（★2）
    - レンダーターゲットのフォーマット（★1）
    - loadOp storeOp
  - レンダーターゲット（FrameBuffer）（★1）
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
  - シェーダーバインドオーバーライト（vkCmdPushDescriptorSetKHR）
  - 他にも DYNAMIC_STATE で指定されたものが設定可能
- トリガー
  - 描画系
  - コンピュート

**レンダーパスの互換性について**

https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#renderpass-compatibility

loadOp storeOp などは不一致でも互換とみなされるっぽいので，パイプライン側のレンダーパスはそこは気にしなくて良いっぽい。

**loadOp storeOp について**

パイプラインにおける loadOp storeOp の考え方。

- loadOp
  - VK_ATTACHMENT_LOAD_OP_LOAD: 既存の値を読んでねという意味。ブレンドするときのカラーやデプス参照する場合はこれを指定する。
  - VK_ATTACHMENT_LOAD_OP_DONT_CARE: 既存の値は不要ですという意味。ブレンドが不要のカラーやデプス参照しない場合（Z 値無視して書き込む場合など）はこれを指定する。
- storeOp
  - VK_ATTACHMENT_STORE_OP_STORE: 値を書き込んでねという意味。
  - VK_ATTACHMENT_STORE_OP_DONT_CARE: 値は書き込まなくていいよという意味。半透明レンダーパス等でデプスを書き込まない場合などはこれを指定。

ちなみに VK_ATTACHMENT_LOAD_OP_CLEAR は RenderPassBegin 時のみ指定。バッファクリアで使う。

### DirectX 12（コマンドリスト）

★ マークがあるところは他の箇所と値を一致させる必要あり。

- パイプラインステート
  - ルートシグネチャのポインタ（★1）
    - ルートシグネチャ（=シェーダーバインド宣言）
      - コンスタントバッファビュー
      - テクスチャビュー（シェーダーリソースビュー）
      - サンプラー
      - ストレージバッファビュー（UAV:unordered access view）
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
- ルートデスクリプタテーブル（=シェーダーバインド実体）
- その他の直接設定
  - レンダーターゲット設定（★2）
  - ビューポート
  - シザー矩形
  - ブレンド係数カラー値
  - ステンシルテスト参照値
  - プリミティブトポロジ（★3）
  - 頂点バッファ・インデックスバッファ
  - インラインコンスタントデータ（SetGraphicsRoot32BitConstant）
  - インラインコンスタントバッファビュー（SetGraphicsRootConstantBufferView）
- トリガー
  - レンダーターゲットのクリア
  - 描画系

**パイプラインステートに渡すルートシグネチャ**

こちらのまとめによると，パイプラインステートとコマンドリストに渡すルートシグネチャオブジェクトは別のものでもいいらしい。たぶん構造が同じならオッケーということなのでしょうきっと。

https://dench.flatlib.jp/d3d/d3d12/descriptor

**パイプラインステートのシリアライズ**

https://shobomaru.wordpress.com/2015/07/22/d3d12-pipeline-state/

シェーダーバインドの宣言部が一緒ならシリアライズできるということなのかな？と理解。

**シェーダーバインドの実体設定はヒープとヒープの中にある**

ヒープの設定は SetDescriptorHeaps で。テーブルの先頭アドレス設定は SetGraphicsRootDescriptorTable で。

テーブルは Descriptor が並んでいるものと考えれば OK。

データの実体は CreateConstantBufferView 等で Descriptor に設定する。

Descriptor はデータやアドレスの参照ハンドルと考えればだいたい OK。

最終的にコマンドリストに渡すのは最初に書いたヒープとテーブルコレなので，シェーダーバインドの実体を渡すコマンドとしてはここ。

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
- アーギュメントバッファ（全部指定する必要なし・シェーダーバインド宣言＆実体として扱い可能・MTLFunction から生成可能）
  - コンスタントバッファビュー・ストレージバッファビュー（MTLBuffer : MTLResource）
  - テクスチャビュー（MTLTexture : MTLResource）
  - サンプラー（MTLSamplerState）
  - インラインコンスタントデータ（setVertexBufferBytes/setFragmentBufferBytes）
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

## キューの並列実行

- Queue の優先度は DirectX 12 形式を採用。Metal では優先度の概念はないがそこは断念。

### Vulkan

- メイン Queue とは別の専用の Queue を用意することで実現。
- [優先度設定](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-priority)もあり。メイン Queue より低い優先度で実行といったことも可能。0.0f〜1.0f で指定し値が大きい方が高優先。

### DirectX 12

- Vulkan と同様に Queue を２つ作る方式。
- [優先度](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_command_queue_priority)は NORMAL、HIGH、GLOBAL_REALTIM の３種類。

### Metal

- [Queue を２つ作成](https://developer.apple.com/documentation/metal/synchronization/synchronizing_events_within_a_single_device)するのは一緒。
- 優先度設定は見つからなかった。

## キュー間同期

- 同期オブジェクトの名前はイベントで。引数値指定は Vulkan ができないのでなし。
- キュー間同期はキューに対して Wait と Signal を登録する DX12 形式で。
- Vulkan は Wait と Signal が呼ばれたイベントを保持しておいて Queue の present のタイミングで vkQueueSubmit する実装がよさそう。

```c++

computeQueue.PushCommand(cmd):
computeQueue.PushSignal(computeSyncSem):
computeQueue.Submit(fence: nullptr);

queue.PushWait(swapchain); // Swapchain が利用可能になるまで待つ。 *1
queue.PushCommand(cmd);
queue.PushWait(computeSyncSem); // *2
queue.PushCommand(cmd);
queue.PushCommand(cmd); // 最後の drawcmd
queue.PushPresent(swapchain);  // *3
queue.Submit(completeFence); // これまでに Queue に詰まれたものを一気に消化 *4

// *1
// Vulkan ではここで 対象 swapchain の内部でかかえる acquire 用 Semaphore を待つ。
// 他のライブラリでは何もしない。

// *2
// Wait のあとは１つ以上の PushCommand もしくは PushPresent を呼んでからでないと Submit() できないものとする。
// これは Vulkan の制限に併せた仕様。

// *3
// PushPresent の Vulkan の実装メモ。
// swapchain の抱える内部処理用 Semaphore を 直前の Execute の終わりで Signal するようにする。
// 
// コードのイメージ
// queue.PushSignal(swapchain.waitSemaphore);
// queue.PushWait()

// *4
// Vulkan は Present での Fence に対応していない。
// そのため Submit 時に Fence が渡された場合、
// コマンドがつまれていたらそこの終了時に Fence に Signal にとぶようにする。
// コマンドが１つもつまれていなかったら何もできないので
// Submit に Fence を渡すときの制約として「１つ以上のコマンドをつむ」を課す。
```

### Vulkan

- Queue 間の同期は２種類。
  - セマフォ：Queue Family の制限は受けない。コマンドバッファの途中に挟めない。
  - イベント：同じ Queue Family で使用可能。コマンドバッファの途中に挟める。
- セマフォは vkQueueSubmit の引数で開始時に待つセマフォと終了時にシグナルを出すセマフォが指定できる。
- vkQueueSubmit は Queue に１つ以上のコマンドバッファを登録する関数。

### DirectX 12

- Queue 間の同期はフェンス。ID3D12Fence。
  - コマンドバッファの途中に挟めない。
  - CPU&GPU 間の同期でも使える。
  - ID3D12Device::CreateFence() で作成。
  - ID3D12CommandQueue.Signal() でシグナルが詰める。引数で 64bit 整数値も渡せる。
  - ID3D12CommandQueue.Wait() で待つコマンドが詰める。

### Metal

- Queue 間の同期は[イベント](https://developer.apple.com/documentation/metal/mtlevent)。
  - コマンドバッファ（コマンドエンコーダ）の途中に挟めない。
  - MTLDevice.makeEvent() で作成。
  - MTLCommandBuffer.encodeSignalEvent() でシグナルが詰める。引数で 64bit 整数値も渡せる。
  - MTLCommandBuffer.encodeWaitForEvent() で待ちコマンドが詰める。

## メモリバリア

- 考えられるメモリバリア
  - GPU メモリにコピーしたバッファをリソース（イメージ，頂点，インデックス，インダイレクト描画引数，他）として使用できるようにする。
  - Present 状態のレンダーターゲットのバッファをレンダーターゲットとして使用できるようにする。
  - レンダーターゲットとして使用していたバッファをイメージとして使用できるようにする。
  - レンダーターゲットとして使用していたバッファをコピー元として使用できるようにする。
  - レンダーターゲットとして使用していたバッファを Present として使用できるようにする。
  - レンダーターゲットにバインドされていたデプスバッファをイメージとして使用できるようにする。
  - レンダーターゲットにバインドされていたデプスバッファをコピー元として使用できるようにする。
  - コピー先のバッファをリソースとして使用できるようにする。
  - コンピュートシェーダの計算結果を格納するストレージバッファをリソースとして使用できるようにする。インダイレクト描画引数も含む。
  - コンピュートシェーダの計算結果を格納するストレージバッファをコピー元として使用できるようにする。
  - CPU メモリから GPU メモリにコピーする前はたしかバリア不要。Map&Unmap したときに確定扱いになるという認識。
- ライブラリ比較
  - 状態遷移バリアに関して３ライブラリとも before-state after-state の概念はある。指定の細かさは異なる。
  - Vulkan と Metal は更に細かく「どのタイミングからどのタイミングまでに」の指定の概念 stage-after stage-before がある。
  - DirectX 12 にのみ分割バリアの概念がある。
- エイリアスバリア
  - 使ったことないのでイメージがわきづらい。
  - 例えば動的解像度で同じバッファを別レンダーターゲットとして使うときはこれ？
- 抽象化設計
  - 少なくとも，Vulkan と DirectX 12 は遷移バリアが必須なので，その API を用意するのはそれほどずれていなさそう。
  - 遷移バリアは Vulkan ベースで。余裕があれば stage-after stage-before まで指定できるようにしてみる。
  - エイリアスバリアは使いどころが見えないのでひとまず保留。

### Vulkan

- [パイプラインバリア](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdPipelineBarrier.html)。A の処理を B までに終わらせておいてね、的な感じで書ける。（[解説サイト 1](https://gpuopen.com/learn/vulkan-barriers-explained/)　[解説サイト 2](https://glhub.blogspot.com/2017/11/vulkan-vkcmdpipelinebarriervkpipelinest.html)）
- 更に引数プロパティの MemoryBarrier、BufferMemoryBarrier, ImageMemoryBarrier で対象となるリソースや遷移（DX12 の TransitionBarrier/AliasBarrier に相当）を指定してバリアをはれる。
  - サンプルが少なくて理解が難しい。
- BufferMemoryBarrier の状態の種類は[こちら](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkAccessFlagBits.html)。
- ImageMemoryBarrier の状態の種類は[こちら](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkImageLayout.html)。
- 細かい[PipelineStage](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkPipelineStageFlagBits.html) の指定が可能。 DirectX 12 にはない。Metal には Vulkan ほど細かくないがある。

### DirectX 12

- [参考](https://docs.microsoft.com/ja-jp/windows/win32/direct3d12/using-resource-barriers-to-synchronize-resource-states-in-direct3d-12#split-barriers)
- TransitionBarrier：レンダーターゲットが読み取りテクスチャになるよといった状態遷移を扱うバリア。
- 状態の種類は[こちら](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ne-d3d12-d3d12_resource_states)。分かりづらいがビットマスクで複数指定可能。
- AliasingBarrier：A という Resource オブジェクトがこれ以降で B という Resouce オブジェクトとして使われることを宣言するバリア。
- UavBarrier：ストレージバッファの書き込み処理をここまでに終わらせてというバリア。Dispatch した結果を別の Dispatch で参照する場合に使う。
- 各種バリアに分割バリアという指定方式もある。ここからこの区間で完了させておいてねーという宣言ができ、パイプラインの最適化のヒントとなる。

### Metal

- コマンドバッファ内・コマンドバッファ間の同期はフェンス・バリア。
  - [フェンス](https://developer.apple.com/documentation/metal/mtlfence)：DX12 でいう AliasingBarrier と同じ。MTLHeap（メモリプール）を使って手動でリソースメモリ管理をして同じアドレスに別リソースオブジェクトを割り当てているときに使う。
  - バリア([1](https://developer.apple.com/documentation/metal/mtlrendercommandencoder/2967442-memorybarrier),[2](https://developer.apple.com/documentation/metal/mtlrendercommandencoder/3019524-memorybarrier))：ここまでに特定のリソースに対しての処理や特定のパイプラインステージに対する処理を終わらせてという宣言。

## CPUGPU 間同期

- Vulkan 仕様ベースのフェンスで抽象化。名前もフェンスで。
- 引数の値指定はなし。キューの submit 時に渡す。
- Metal の場合は CommandBuffer に対して行うので，最後に commit された CommandBuffer をキューが覚えておいて，submit 時に良い感じにすれば抽象化できる。

### Vulkan

- フェンス。vkFence オブジェクト。
- Queue の submit 時の引数で１つ指定。
- vkWaitForFences で待ち，vkResetFences でリセット。これらは複数の vkFence が指定可能。
- vkFence は DirectX12 のように値を渡す仕組みはない。

### DirectX 12

- フェンス。
- ID3D12CommandQueue.Signal() でシグナルが詰める。引数で値も渡せる。
- ID3D12Fence.SetEventOnCompletion() で待機用に使う Event オブジェクト指定。指定の値がきたら Event にシグナルが送信される。

### Metal

- [MTLCommandBuffer.waitUntilCompleted()](https://developer.apple.com/documentation/metal/mtlcommandbuffer/1443039-waituntilcompleted) で待つ。

# 最適化

## セカンダリコマンドバッファ

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

- 全て同じように機能はそろっている。

### Vulkan

- [vkCmdDrawIndexedIndirect](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdDrawIndexedIndirect.html)

### DirectX 12

- [ID3D12GraphicsCommandList::ExecuteIndirect](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12graphicscommandlist-executeindirect)

### Metal

- https://developer.apple.com/documentation/metal/mtlrendercommandencoder/specifying_drawing_and_dispatch_arguments_indirectly

## バッファ生成時初期値指定

DirectX 12 のみ CreateReservedResource() や CreateCommittedResource() でイメージバッファ・デプスステンシルバッファに対してクリアカラーが指定できる。
ここで指定した毎フレームクリアするカラーと一致する場合はパフォーマンスが良くなるのだとか。

# 付録

## 参考

- [A Comparison of Modern Graphics APIs](https://alain.xyz/blog/comparison-of-modern-graphics-apis)
- [Veldrid (low-level graphics library for .NET)](https://veldrid.dev/articles/intro.html)
