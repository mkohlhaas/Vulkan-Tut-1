#pragma once

#include "types.h"

extern Vertex *vertices;
extern size_t numVertices;

// Fills `vertices` and `indices`.
bool loadMesh(const char *filename);
