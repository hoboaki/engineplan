// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0

layout(std140, set = LAYOUT_SET_BUFFER, binding = 0) uniform UbufType {
    mat4 mvp;
} Ubuf;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Uv0;

layout(location = 0) out vec3 FragPos;
layout(location = 1) out vec2 FragUv0;

void main() 
{
   gl_Position = Ubuf.mvp * vec4(Position, 1.0);
   FragPos = gl_Position.xyz;
   FragUv0 = Uv0;
}

// EOF
