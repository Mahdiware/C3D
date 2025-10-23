//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_VERTEX_H
#define C_3D_RENDERING_ENGINE_VERTEX_H
#include "engine/vec3/vec3.h"

typedef struct {
    vec3 position;
    vec3 color;
}Vertex;

typedef struct {
    Vertex *vertex;
    int rendered;
} VertexArray;

Vertex *initialize_vertex(vec3 position, vec3 color);

#endif //C_3D_RENDERING_ENGINE_VERTEX_H