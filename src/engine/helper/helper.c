//
// Created by arjun on 10/22/25.
//

#include "helper.h"


vec3 vec2ToVec3(vec2 vector2) {
    return (vec3){vector2.x, vector2.y, 0};
}
Color getColor() {
    Color c;
    c.red =  (vec3) {1.0f, 0.0f, 0.0f};
    c.green = (vec3) {0.0f, 1.0f, 0.0f};
    c.blue = (vec3) {0.0f, 0.0f, 1.0f};
    return c;
}