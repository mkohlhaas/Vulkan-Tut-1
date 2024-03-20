#include "types.h"

uint8_t currentFrame = 0;

const Vertex vertices[] = {
    {{+0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{+0.5f, +0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, +0.5f}, {0.0f, 0.0f, 1.0f}},
};

size_t numVertices = sizeof(vertices) / sizeof(Vertex);
