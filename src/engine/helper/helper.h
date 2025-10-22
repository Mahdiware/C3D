//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_HELPER_H
#define C_3D_RENDERING_ENGINE_HELPER_H
#include "engine/vec3/vec3.h"
#include "engine/vec2/vec2.h"

vec3 vec2ToVec3(vec2 vector2);
typedef struct {
    vec3 red;
    vec3 green;
    vec3 blue;
} Color;
Color getColor();
#endif //C_3D_RENDERING_ENGINE_HELPER_H