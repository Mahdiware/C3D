//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_VEC3_H
#define C_3D_RENDERING_ENGINE_VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec3d;

vec3 init_vec3(float x, float y, float z);
#endif //C_3D_RENDERING_ENGINE_VEC3_H