//
// Created by arjun on 10/22/25.
//

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void noUpdate(void *k,double d) {
    printf("NoUpdate\n");
}
Object *initialize_object() {
    Object *object = malloc(sizeof(Object));
    object->total_vertices = 0;
    object->vertices = NULL;
    object->mode = GL_TRIANGLES;
    object->update = noUpdate;
    return object;
}
void add_vertex(Object *object, Vertex *vertex) {
    object->vertices = realloc(object->vertices, sizeof(Vertex) * (object->total_vertices + 1));
    if (!object->vertices) {
        object->total_vertices = 0;
        return;
    }
    // Copy the new vertex into the array
    object->vertices[object->total_vertices] = *vertex;
    object->total_vertices++;
}

void remove_vertex(Object *object, Vertex *vertex) {
    if (!object || object->total_vertices == 0) return;

    int found_index = -1;
    for (int i = 0; i < object->total_vertices; i++) {
        if (memcmp(&object->vertices[i], vertex, sizeof(Vertex)) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) return;
    for (int i = found_index; i < object->total_vertices - 1; i++) {
        object->vertices[i] = object->vertices[i + 1];
    }

    object->total_vertices--;
    if (object->total_vertices > 0) {
        object->vertices = realloc(object->vertices, sizeof(Vertex) * object->total_vertices);
    } else {
        free(object->vertices);
        object->vertices = NULL;
    }
}

void on_update(Object *object, update_function update) {
    object->update = update;
}