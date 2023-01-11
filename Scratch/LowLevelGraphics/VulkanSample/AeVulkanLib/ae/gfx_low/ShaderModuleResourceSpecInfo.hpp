// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ShaderModuleResource のデータ構造仕様に関する情報。
class ShaderModuleResourceSpecInfo {
public:
    /// @name プロパティ
    //@{
    /// バイトコードのサイズ。（初期値：0）
    size_t Size() const { return size_; }

    /// Size() の設定。
    /// @param size 0以上。
    ShaderModuleResourceSpecInfo& SetSize(size_t size)
    {
        size_ = size;
        return *this;
    }
    //@}

private:
    size_t size_ = 0;
};

} // namespace ae::gfx_low
// EOF
