// 文字コード：UTF-8
#include <aesk/GeometrySquare.hpp>

// includes
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace aesk {

namespace {

// clang-format off
const float fPositionData[] = {
    -1.0f, 1.0f, 0.0f,
    -1.0f,-1.0f, 0.0f,
     1.0f, 1.0f, 0.0f,
    -1.0f,-1.0f, 0.0f,
     1.0f,-1.0f, 0.0f,
     1.0f, 1.0f, 0.0f,
};

const float fNormalData[] = {
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
};

const float fUv0Data[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};
// clang-format on
} // namespace

//------------------------------------------------------------------------------
GeometrySquare::GeometrySquare(const float size)
: buffer_() {
    AE_BASE_ASSERT_LESS(0.0f, size);
    const float halfSize = size * 0.5f;
    for (int i = 0; i < VertexCountValue; ++i) {
        auto& vtx = buffer_.v[i];
        vtx.position[0] = fPositionData[i * 3 + 0] * halfSize;
        vtx.position[1] = fPositionData[i * 3 + 1] * halfSize;
        vtx.position[2] = fPositionData[i * 3 + 2] * halfSize;
        vtx.normal[0] = fNormalData[i * 3 + 0];
        vtx.normal[1] = fNormalData[i * 3 + 1];
        vtx.normal[2] = fNormalData[i * 3 + 2];
        vtx.uv0[0] = fUv0Data[i * 2 + 0];
        vtx.uv0[1] = fUv0Data[i * 2 + 1];
    }
}

} // namespace aesk
// EOF
