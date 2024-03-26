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
    float ambientFactor = 0.0f;
    vec3 ambientColor = vec3(0.3f);
    vec3 ambient = ambientFactor * ambientColor;

    // diffuse light
    float diffuseFactor = 1.0f;
    vec3 diffuseColor = vec3(0.5f, 0.0f, 0.5f);
    vec3 diffuse = diffuseFactor * max(dot(N, L), 0) * diffuseColor;

    // specular light
    float specularFactor = 1.0f;
    float shininess = 16.0f;
    vec3 specularColor = vec3(0.5f, 1.0f, 0.0f);
    vec3 specular = specularFactor * pow(max(dot(R, V), 0), shininess) * specularColor;

    outColor = vec4(ambient + diffuse + specular, 1.0f);
}
