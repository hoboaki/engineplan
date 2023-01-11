// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>

namespace ae::gfx_low {
class IndirectBufferView;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// CmdDrawIndirect に必要な情報。
class DrawIndirectCallInfo {
public:
    /// @name プロパティ
    //@{
    /// 使用するインダイレクトバッファ。（初期値：0）
    const IndirectBufferView* IndirectBufferView() const
    {
        return indirectBufferView_.Get();
    }

    /// IndirectBufferView() の設定。（設定必須）
    DrawIndirectCallInfo& SetIndirectBufferView(
        const gfx_low::IndirectBufferView* view)
    {
        indirectBufferView_.Reset(view);
        return *this;
    }

    /// インデックスバッファの起点となる番号。 （初期値：0）
    int CommandOffset() const { return commandOffset_; }

    /// CommandOffset() の設定。
    /// @param offset 0以上。
    DrawIndirectCallInfo& SetCommandOffset(int offset);

    /// 処理をするコマンド数。 （初期値：0）
    int CommandCount() const { return commandCount_; }

    /// CommandCount() の設定。
    /// @param count 1以上。
    DrawIndirectCallInfo& SetCommandCount(int count);

    /// インデックスバッファを使用するか。 （初期値：false）
    bool UseIndexBuffer() const { return useIndexBuffer_; }

    /// UseIndexBuffer() の設定。
    DrawIndirectCallInfo& SetUseIndexBuffer(bool useIndexBuffer)
    {
        useIndexBuffer_ = useIndexBuffer;
        return *this;
    }
    //@}

private:
    ::ae::base::Pointer<const gfx_low::IndirectBufferView> indirectBufferView_;
    int commandCount_ = 0;
    int commandOffset_ = 0;
    bool useIndexBuffer_ = false;
};

} // namespace ae::gfx_low
// EOF
