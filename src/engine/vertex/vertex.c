//
// Created by arjun on 10/22/25.
//

#include "vertex.h"

#include <stdlib.h>


Vertex *initialize_vertex(vec3 position, vec3 color) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->position = position;
    vertex->color = color;
    return vertex;
}
