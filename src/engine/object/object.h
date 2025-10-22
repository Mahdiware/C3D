//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_OBJECT_H
#define C_3D_RENDERING_ENGINE_OBJECT_H
#include "engine/vertex/vertex.h"

#include <GLFW/glfw3.h>
typedef struct {
    GLenum mode;
    int total_vertices;
    Vertex *vertices;
} Object;

Object *initialize_object();
void add_vertex(Object *object, Vertex *vertex);
void remove_vertex(Object *object, Vertex *vertex);

#endif //C_3D_RENDERING_ENGINE_OBJECT_H