// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0
#define LAYOUT_SET_IMAGE 1
#define LAYOUT_SET_SAMPLER 2

layout(location = 0) in vec3 FragViewPos; // ビュー空間の位置
layout(location = 1) in vec3 FragViewNormal; // ビュー空間の法線

layout(location = 0) out vec4 FragColor;

layout(set = LAYOUT_SET_IMAGE, binding = 0) uniform textureCube Image0;
layout(set = LAYOUT_SET_SAMPLER, binding = 0) uniform sampler Sampler0;

void main() {
   vec3 eyeToPos = normalize(FragViewPos);
   vec3 normal = normalize(FragViewNormal);
   vec3 reflectVec = reflect(eyeToPos, normal);
   FragColor = texture(samplerCube(Image0, Sampler0), reflectVec);
}

// EOF
