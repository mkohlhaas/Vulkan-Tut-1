#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 light;
} ubo;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec3 fragView;
layout(location = 2) out vec3 fragLight;

void main() {
    vec4 worldPos = ubo.model * vec4(position, 1.0);
    gl_Position = ubo.proj * ubo.view * worldPos;

    fragNormal = (ubo.view * ubo.model * vec4(normal, 0.0f)).xyz;
    fragView = -(ubo.view * worldPos).xyz;
    fragLight = (ubo.view * ubo.model * ubo.light).xyz;
}
