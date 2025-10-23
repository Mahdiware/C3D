//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_TRIANGLE_H
#define C_3D_RENDERING_ENGINE_TRIANGLE_H

#include "engine/Mesh/mesh.h"
#include "engine/object/object.h"
#include "engine/vec2/vec2.h"
#include "engine/vec3/vec3.h"
#include "engine/vertex/vertex.h"


typedef struct Triangle_t {
    vec3 a, b, c;
}Triangle;

Triangle init_triangle(vec2 a, vec2 b, vec2 c) ;
Triangle from_vertices(Vertex *verticies, int num_vertices);
Triangle init_triangle_3(vec3 a, vec3 b, vec3 c) ;
Object *get_triangle_object_filled(Triangle t, vec3 *c, int colors);
vec3 getNormalVector(Triangle t);
#endif //C_3D_RENDERING_ENGINE_TRIANGLE_H