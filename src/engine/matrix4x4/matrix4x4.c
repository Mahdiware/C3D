#include "matrix4x4.h"
#include "math.h"

matrix4x4 rotX(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = 1;
    m.a[1][1] = cos(angle); m.a[1][2] = -sin(angle);
    m.a[2][1] = sin(angle); m.a[2][2] = cos(angle);
    m.a[3][3] = 1;
    return m;
}

matrix4x4 rotY(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = cos(angle); m.a[0][2] = -sin(angle);
    m.a[1][1] = 1;
    m.a[2][0] = sin(angle); m.a[2][2] = cos(angle);
    m.a[3][3] = 1;
    return m;
}

matrix4x4 rotZ(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = cos(angle); m.a[0][1] = sin(angle);
    m.a[1][0] = -sin(angle); m.a[1][1] = cos(angle);
    m.a[2][2] = 1; m.a[3][3] = 1;
    return m;
}