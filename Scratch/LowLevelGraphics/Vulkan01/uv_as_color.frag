// 文字コード：UTF-8
#version 400
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
// layout (binding = 1) uniform sampler2D tex;

layout (location = 0) in vec2 Texcoord;
layout (location = 1) in vec3 FragPos;
layout (location = 0) out vec4 FragColor;

const vec3 LightDir = vec3(0.424, 0.566, 0.707);

void main() {
   vec3 dX = dFdx(FragPos);
   vec3 dY = dFdy(FragPos);
   vec3 normal = normalize(cross(dX,dY));
   float light = max(0.0, dot(LightDir, normal));
   //FragColor = light * texture(tex, Texcoord.xy);
   FragColor = light * vec4(Texcoord.xy, 1.0, 1.0);
}

// EOF
