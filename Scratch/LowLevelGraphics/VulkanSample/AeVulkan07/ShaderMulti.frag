// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

#define LAYOUT_SET_BUFFER 0
#define LAYOUT_SET_IMAGE 1
#define LAYOUT_SET_SAMPLER 2

layout(location = 0) in vec3 FragPos;
layout(location = 1) in vec2 FragUv0;
layout(location = 2) in vec2 FragUv1;
layout(location = 0) out vec4 FragColor0;
layout(location = 1) out vec4 FragColor1;

void main() {
    // 0番にUV値をカラーに変換した色を、1番に円形マスクを出力。
    vec2 offset = (FragUv0 - vec2(0.5, 0.5));
    float circleMask = (sqrt(dot(offset, offset)) < 0.45) ? 1 : 0;
    vec2 tmpXy = abs(mod(FragUv1, vec2(2, 2)) - vec2(1, 1));
    FragColor0 = vec4(tmpXy, 0, 1);
    FragColor1 = vec4(vec3(1, 1, 1) * circleMask, 1);
}

// EOF
