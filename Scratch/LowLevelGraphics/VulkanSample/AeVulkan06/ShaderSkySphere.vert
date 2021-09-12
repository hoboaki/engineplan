// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0

layout(std140, set = LAYOUT_SET_BUFFER, binding = 0) uniform UbufSceneType {
    mat4 projMtx;
    mat4 viewMtx;
    mat4 invViewMtx;
} UbufScene;

layout(std140, set = LAYOUT_SET_BUFFER, binding = 1) uniform UbufModelType {
    mat4 modelMtx;
} UbufModel;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 Uv0;

layout(location = 0) out vec3 FragViewPos; // ビュー空間の位置
layout(location = 1) out vec3 FragViewNormal; // ビュー空間の法線
layout(location = 2) out vec3 FragWorldPos; // ワールド空間の位置
layout(location = 3) out vec3 FragWorldNormal; // ワールド空間の法線

void main() {
    vec4 worldPos = UbufModel.modelMtx * vec4(Position, 1.0);
    vec4 viewPos = UbufScene.viewMtx * worldPos;
    vec3 worldNormal = mat3(UbufModel.modelMtx) * Normal; 
    vec3 viewNormal = mat3(UbufScene.viewMtx) * worldNormal;
    gl_Position = UbufScene.projMtx * viewPos;
    FragViewPos = viewPos.xyz;
    FragViewNormal = viewNormal;
    FragWorldPos = worldPos.xyz;
    FragWorldNormal = worldNormal;
    gl_Position.y = -gl_Position.y; // フレームバッファ空間の-Y方向をY-Upに変換
}

// EOF
