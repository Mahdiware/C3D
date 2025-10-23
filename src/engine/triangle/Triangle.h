//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_TRIANGLE_H
#define C_3D_RENDERING_ENGINE_TRIANGLE_H
#include "engine/helper/helper.h"
#include "engine/Mesh/mesh.h"
#include "engine/object/object.h"
#include "engine/vec2/vec2.h"


typedef struct Triangle_t {
    vec3 a, b, c;
}Triangle;

Triangle init_triangle(vec2 a, vec2 b, vec2 c) ;
Triangle init_triangle_3(vec3 a, vec3 b, vec3 c) ;
Object *get_triangle_object_filled(Triangle t, vec3 *c, int colors);
Mesh *get_triangle_object_line(Triangle t, vec3 *c, int colors);

#endif //C_3D_RENDERING_ENGINE_TRIANGLE_H