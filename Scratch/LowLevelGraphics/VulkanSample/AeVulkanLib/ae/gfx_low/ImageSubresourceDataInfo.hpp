// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// ImageSubresource のデータ情報。
class ImageSubresourceDataInfo {
public:
    /// @name コンストラクタ
    //@{
    /// 全て0で作成。
    ImageSubresourceDataInfo() {}

    /// 初期値を指定して作成。
    ImageSubresourceDataInfo(size_t offset, size_t rowPitch, size_t depthPitch)
    : offset_(offset)
    , rowPitch_(rowPitch)
    , depthPitch_(depthPitch)
    {
    }
    //@}

    /// @name プロパティ
    //@{
    /// ImageResource の抱える ResourceMemory の先頭アドレスからのオフセット値。
    size_t Offset() const { return offset_; }

    /// Y方向に+1移動する際のバイトサイズ。
    size_t RowPitch() const { return rowPitch_; }

    /// Z方向に+1移動する際のバイトサイズ。
    size_t DepthPitch() const { return depthPitch_; }
    //@}

private:
    size_t offset_ = 0;
    size_t rowPitch_ = 0;
    size_t depthPitch_ = 0;
};

} // namespace ae::gfx_low
// EOF
