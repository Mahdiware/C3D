//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_VERTEX_H
#define C_3D_RENDERING_ENGINE_VERTEX_H
typedef struct {
    float x, y, z;
    float r, g, b;
}Vertex;

Vertex *initialize_vertex(float x, float y, float z, float r, float g, float b);

#endif //C_3D_RENDERING_ENGINE_VERTEX_H