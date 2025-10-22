//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_TRIANGLE_H
#define C_3D_RENDERING_ENGINE_TRIANGLE_H
#include "engine/object/object.h"
#include "engine/vec2/vec2.h"


typedef struct Triangle_t {
    vec2 a, b, c;
}Triangle;

Triangle init_triangle(vec2 a, vec2 b, vec2 c) ;
Object *get_triangle_object(Triangle t);
#endif //C_3D_RENDERING_ENGINE_TRIANGLE_H