// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location = 0) in vec3 Position;
layout(location = 0) out vec2 FragUv0;

void main() {
    gl_Position = vec4(Position.xy, 0.0, 1.0);
}

// EOF
