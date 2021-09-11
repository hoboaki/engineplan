// 文字コード：UTF-8
#pragma once

#include <ae/base/MemBlock.hpp>

//------------------------------------------------------------------------------
namespace aesk {

/// 正方形（XY平面）の頂点データ。
/// @details
/// (0,0,0) を中心にコンストラクタで指定したサイズの正方形の頂点データを生成します。
class GeometrySquare {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @param size １辺の長さ。（0より大きい値）
    GeometrySquare(float size = 2.0f);
    //@}

    /// @name 取得
    //@{
    /// 頂点数。
    int VertexCount() const { return VertexCountValue; }

    /// １頂点あたりのデータサイズ。
    int Stride() const {
        return sizeof(VertexType);
    }

    /// 先頭から位置データまでのアドレス距離。
    int OffsetPosition() const {
        return 0;
    }

    /// 先頭から法線データまでのアドレス距離
    int OffsetNormal() const {
        return 3 * sizeof(float);
    }

    /// 先頭からUv0データまでのアドレス距離。
    int OffsetUv0() const {
        return 6 * sizeof(float);
    }

    /// 頂点データ。
    ::ae::base::MemBlock Data() const {
        return ::ae::base::MemBlock(&buffer_, sizeof(buffer_));
    }
    //@}

private:
    static constexpr int VertexCountValue = 2 * 3;
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

} // namespace aesk
// EOF
