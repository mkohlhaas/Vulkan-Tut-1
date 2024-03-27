#version 450

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragView;
layout(location = 2) in vec3 fragLight;

layout(location = 0) out vec4 outColor;

layout(push_constant) uniform PushConstants {
    int mode;
} shader;

void main() {
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(fragView);
    vec3 L = normalize(fragLight);
    vec3 R = reflect(-L, N);

    // ambient light
    float ambientFactor = 0.0f; // ambient reflection coefficient
    vec3 ambientColor = vec3(0.3f);
    vec3 ambient = ambientFactor * ambientColor;

    // diffuse light
    float diffuseFactor = 1.0f; // diffuse reflection coefficient
    vec3 diffuseColor = vec3(0.5f, 0.0f, 0.5f);
    vec3 diffuse = diffuseFactor * max(dot(N, L), 0) * diffuseColor;

    // specular light
    float specularFactor = 1.0f; // specular reflection coefficient
    float shininess = 16.0f;
    vec3 specularColor = vec3(0.5f, 1.0f, 0.0f);
    vec3 specular = specularFactor * pow(max(dot(R, V), 0), shininess) * specularColor;

    if (shader.mode == 0) { // Phong Shader
        outColor = vec4(ambient + diffuse + specular, 1.0f);
    } else if (shader.mode == 1) { // Toon Shader
        if (pow(max(dot(R, V), 0), shininess) > 0.2f) {
            outColor = vec4(specularColor, 1.0f);
        } else if (dot(V, N) < 0.5f) {
            outColor = vec4(diffuseColor, 1.0f);
        } else if (dot(N, L) >= 0.1f) {
            outColor = vec4(0.5f, 0.3f, 0.4f, 1.0f);
        } else {
            outColor = vec4(ambientColor, 1.0f);
        }
    } else if (shader.mode == 2) { // Constant Shader
        outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
}
