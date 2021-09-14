// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_IMAGE 0
#define LAYOUT_SET_SAMPLER 1

layout(location = 0) in vec2 FragUv0;
layout(location = 0) out vec4 FragColor;

layout(set = LAYOUT_SET_IMAGE, binding = 0) uniform texture2D Image0;
layout(set = LAYOUT_SET_SAMPLER, binding = 0) uniform sampler Sampler0;

void main() {
    FragColor = texture(sampler2D(Image0, Sampler0), FragUv0.xy);
}
// EOF
