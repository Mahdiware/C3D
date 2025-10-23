//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_HELPER_H
#define C_3D_RENDERING_ENGINE_HELPER_H
#include "engine/vec3/vec3.h"
#include "engine/vec2/vec2.h"
#include "engine/matrix4x4/matrix4x4.h"
#include "engine/vertex/vertex.h"

vec3d multiplyMatrix4x4AndVec3(vec3 in, matrix4x4 matrix);
matrix4x4 get_projection_matrix(int height, int width, float fov, float far, float near) ;

vec3 vec2ToVec3(vec2 vector2);
vec3 reverse_vec3(vec3 vector3);
vec2 screen_to_ndc(float x, float y, float width, float height);

typedef struct {
    vec3 red;
    vec3 green;
    vec3 blue;
} Color;
vec3 fromVertex(Vertex v);
vec3 fromVec3d(vec3d v);
Color getColor();
#endif //C_3D_RENDERING_ENGINE_HELPER_H