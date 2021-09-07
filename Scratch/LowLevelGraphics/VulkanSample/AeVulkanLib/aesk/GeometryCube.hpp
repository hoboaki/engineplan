// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// 立方体の頂点データ。
/// @details
/// (0, 0, 0)を中心にコンストラクタで指定したサイズの立方体の頂点データを生成します。
class GeometryCube {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param size 立方体の１辺の長さ。（0より大きい値）
    GeometryCube(float size = 2.0f);
    //@}

    /// @name 取得
    //@{
    int VertexCount() const { return VertexCountValue; } ///< 頂点数。
    int Stride() const { return sizeof(VertexType); } ///< １頂点あたりのデータサイズ。
    int OffsetPosition() const { return 0; }  ///< 先頭から位置データまでのアドレス距離。
    int OffsetNormal() const { return 3 * sizeof(float); } ///< 先頭から法線データまでのアドレス距離
    int OffsetUv0() const { return 6 * sizeof(float); } ///< 先頭からUv0データまでのアドレス距離。

    /// 頂点データ。
    ::ae::base::MemBlock Data() const {
        return ::ae::base::MemBlock(&buffer_, sizeof(buffer_));
    }
    //@}

private:
    static constexpr int VertexCountValue = 12 * 3;
    struct VertexType {
        float position[3];
        float normal[3];
        float uv0[2];
    };
    struct VertexBufferType {
        VertexType v[VertexCountValue];
    };
    VertexBufferType buffer_;
};

}
// EOF
