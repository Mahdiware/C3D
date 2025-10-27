
#include "vec3.h"
#include <math.h>

void normalizeVec3(vec3 *v) {
    float len = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
    if (len > 0.0f) {
        v->x /= len;
        v->y /= len;
        v->z /= len;
    }
}

void copyVec3(vec3 *dest, vec3 *src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}