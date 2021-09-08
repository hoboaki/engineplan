// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0
#define LAYOUT_SET_IMAGE 1
#define LAYOUT_SET_SAMPLER 2

layout(location = 0) in vec3 FragPos;
layout(location = 1) in vec2 FragUv0;
layout(location = 0) out vec4 FragColor;

layout(set = LAYOUT_SET_IMAGE, binding = 0) uniform texture2D ImageColor;
layout(set = LAYOUT_SET_IMAGE, binding = 1) uniform texture2D ImageMask;
layout(set = LAYOUT_SET_SAMPLER, binding = 0) uniform sampler Sampler0;

void main() {
    // ２枚のテクスチャを乗算して出力
    vec4 color = texture(sampler2D(ImageColor, Sampler0), FragUv0.xy);
    vec4 mask = texture(sampler2D(ImageMask, Sampler0), FragUv0.xy);
    FragColor = vec4(color.xyz * mask.xyz, 1.0);
}

// EOF
