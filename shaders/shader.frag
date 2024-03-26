#version 450

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragView;
layout(location = 2) in vec3 fragLight;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(fragView);
    vec3 L = normalize(fragLight);
    vec3 R = reflect(-L, N);

    // ambient light
    vec3 ambientColor = vec3(0.3f);

    // diffuse light
    vec3 diffuseColor = vec3(0.5f, 1.0f, 0.5f);

    // specular light
    float shininess = 16.0f;
    vec3 specularColor = vec3(0.5f, 0.2f, 0.0f);

    if (pow(max(dot(R, V), 0), shininess) > 0.2f) {
        outColor = vec4(specularColor, 1.0f);
    } else if (dot(V, N) < 0.5f) {
        outColor = vec4(diffuseColor, 1.0f);
    } else if (dot(N, L) >= 0.1f) {
        outColor = vec4(0.5f, 0.3f, 0.4f, 1.0f);
    } else {
        outColor = vec4(ambientColor, 1.0f);
    }
}
