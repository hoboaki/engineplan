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
    layout(offset = 16) vec4 addColor;
} DirectConstData;

layout(location = 0) in vec3 FragWorldPos;
layout(location = 1) in vec3 FragWorldNormal;
layout(location = 0) out vec4 FragColor;

const vec3 LightDir = vec3(0.424, 0.566, 0.707);

void main() {
    vec3 eyePos = Ubuf.invViewMtx[3].xyz;
    vec3 eyeToPos = normalize(FragWorldPos - eyePos);
    vec3 normal = normalize(FragWorldNormal);
    vec3 reflectVec = reflect(eyeToPos, normal);
    FragColor = vec4(max(reflectVec, vec3(0)) + DirectConstData.addColor.xyz, 1.0f);
}

// EOF
