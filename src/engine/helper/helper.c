//
// Created by arjun on 10/22/25.
//

#include "helper.h"

#include <math.h>
#include <stdio.h>


vec3 vec2ToVec3(vec2 vector2) {
    return (vec3){vector2.x, vector2.y, 1.0f};
}
Color getColor() {
    Color c;
    c.red =  (vec3) {1.0f, 0.0f, 0.0f};
    c.green = (vec3) {0.0f, 1.0f, 0.0f};
    c.blue = (vec3) {0.0f, 0.0f, 1.0f};
    return c;
}


vec3d multiplyMatrix4x4AndVec3(vec3 in, matrix4x4 m) {
    vec3d out = {0};
    // in.z +=3 ;
    out.x = in.x * m.a[0][0] + in.y * m.a[1][0] + in.z * m.a[2][0] + m.a[3][0];
    out.y = in.x * m.a[0][1] + in.y * m.a[1][1] + in.z * m.a[2][1] + m.a[3][1];
    out.z = in.x * m.a[0][2] + in.y * m.a[1][2] + in.z * m.a[2][2] + m.a[3][2];
    out.w = in.x * m.a[0][3] + in.y * m.a[1][3] + in.z * m.a[2][3] + m.a[3][3];


    // printf("out mat4xt: {%.2f, %.2f, %.2f, %.2f}\n", out.x, out.y, out.z, out.w);

    if (out.w != 0.0f) {
        out.x /= out.w;
        out.y /= out.w;
        out.z /= out.w;

    }

    return out;
}



matrix4x4 get_projection_matrix(int height, int width, float fov, float far, float near) {
    matrix4x4 projection = {0};

    float aspect = (float)width / (float)height;

    // float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
    float fovRad = 1.0f / tanf((fov * 0.5f) * (3.14159f / 180.0f));


    projection.a[0][0] = aspect * fovRad;
    projection.a[1][1] = fovRad;
    projection.a[2][2] = far / (far - near);
    projection.a[3][2] =( -far*near )/ (far - near);
    projection.a[2][3] = 1.0f;
    projection.a[3][3] = 0.0f;
    return projection;
}

vec3 reverse_vec3(vec3 vector3) {
    return (vec3){-vector3.x, -vector3.y, -vector3.z};
}
vec2 screen_to_ndc(float x, float y, float width, float height) {
    return (vec2){
        (x / width) * 2.0f - 1.0f,    // x in [-1,1]
        (y / height) * 2.0f - 1.0f    // y in [-1,1]
    };
}

vec3 fromVertex(Vertex v) {
    return v.position;
}

vec3 fromVec3d(vec3d v) {
    return (vec3){v.x, v.y, v.z};
}