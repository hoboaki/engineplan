// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0

layout(std140, set = LAYOUT_SET_BUFFER, binding = 0) uniform UbufSceneType {
    mat4 projMtx;
    mat4 viewMtx;
} UbufScene;

layout(std140, set = LAYOUT_SET_BUFFER, binding = 1) uniform UbufModelType {
    mat4 modelMtx;
} UbufModel;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Uv0;

layout(location = 0) out vec2 Texcoord;
layout(location = 1) out vec3 FragPos;

void main() 
{
   Texcoord = Uv0;
   gl_Position = UbufScene.projMtx * UbufScene.viewMtx * UbufModel.modelMtx * vec4(Position, 1.0);
   FragPos = gl_Position.xyz;
}

// EOF
