//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_RECT_H
#define C_3D_RENDERING_ENGINE_RECT_H
#include "engine/triangle/Triangle.h"

typedef struct {
    Triangle s1;
    Triangle s2;
} Rect;

Rect* init_rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4);
Mesh* get_rect_mesh(Rect* r, vec3 *colors, int num_colors);
#endif //C_3D_RENDERING_ENGINE_RECT_H