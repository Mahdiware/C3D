//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_OBJECT_H
#define C_3D_RENDERING_ENGINE_OBJECT_H
#include "engine/vertex/vertex.h"

#include <GLFW/glfw3.h>

typedef void (*update_function)(void *, double);

typedef struct {
    GLenum mode;
    int total_vertices;
    Vertex *vertices;

    update_function update;
} Object;

Object *initialize_object();
void add_vertex(Object *object, Vertex *vertex);
void remove_vertex(Object *object, Vertex *vertex);
void on_update(Object *obj, update_function update);

#endif //C_3D_RENDERING_ENGINE_OBJECT_H