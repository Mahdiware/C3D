//
// Created by arjun on 10/22/25.
//

#include "vertex.h"

#include <stdlib.h>


Vertex *initialize_vertex(float x, float y, float z, float r, float g, float b) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    vertex->r = r;
    vertex->g = g;
    vertex->b = b;
    return vertex;
}
