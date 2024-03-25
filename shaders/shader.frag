#version 450

layout(location = 0) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 N = normalize(fragNormal);
    outColor = vec4(N, 1.0f);
}
