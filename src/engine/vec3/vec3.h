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
void copyVec3(vec3 *dest, vec3 *src);
void normalizeVec3(vec3 *v);
#endif //C_3D_RENDERING_ENGINE_VEC3_H