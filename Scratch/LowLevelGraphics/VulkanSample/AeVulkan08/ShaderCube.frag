// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0
#define LAYOUT_SET_IMAGE 1
#define LAYOUT_SET_SAMPLER 2

layout(location = 0) in vec2 Texcoord;
layout(location = 1) in vec3 FragPos;
layout(location = 0) out vec4 FragColor;

layout(set = LAYOUT_SET_IMAGE, binding = 0) uniform texture2D Image0;
layout(set = LAYOUT_SET_SAMPLER, binding = 0) uniform sampler Sampler0;

const vec3 LightDir = vec3(0.424, 0.566, 0.707);

void main() {
    vec3 dX = dFdx(FragPos);
    vec3 dY = dFdy(FragPos);
    vec3 normal = normalize(cross(dX,dY));
    float light = max(0.0, dot(LightDir, normal));
    FragColor = light * texture(sampler2D(Image0, Sampler0), Texcoord.xy);
}

// EOF
