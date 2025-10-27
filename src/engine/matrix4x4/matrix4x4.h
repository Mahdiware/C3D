//
// Created by arjun on 10/23/25.
//

#ifndef C_3D_RENDERING_ENGINE_MATRIX4X4_H
#define C_3D_RENDERING_ENGINE_MATRIX4X4_H

typedef struct {
    float a[4][4];
} matrix4x4;

matrix4x4 rotX(double angle);
matrix4x4 rotY(double angle);
matrix4x4 rotZ(double angle);

#endif //C_3D_RENDERING_ENGINE_MATRIX4X4_H