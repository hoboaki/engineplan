// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0

layout(std140, set = LAYOUT_SET_BUFFER, binding = 0) uniform UbufType {
    mat4 projMtx;
    mat4 viewMtx;
    mat4 invViewMtx;
    mat4 modelMtx;
} Ubuf;

layout ( push_constant ) uniform DirectConstantDataType {
    vec4 instanceTrans;
} DirectConstData;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;

layout(location = 0) out vec3 FragWorldPos;
layout(location = 1) out vec3 FragWorldNormal;

void main() {
    vec4 worldPos = Ubuf.modelMtx * vec4(Position, 1.0);
    worldPos += DirectConstData.instanceTrans;
    FragWorldPos = worldPos.xyz;
    FragWorldNormal = mat3(Ubuf.modelMtx) * Normal;
    gl_Position = Ubuf.projMtx * Ubuf.viewMtx * worldPos;
    gl_Position.y = -gl_Position.y; // フレームバッファ空間の-Y方向をY-Upに変換
}

// EOF
