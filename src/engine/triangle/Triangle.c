//
// Created by arjun on 10/22/25.
//

#include "Triangle.h"

#include "engine/helper/helper.h"

#include "math.h"
void rotateTriangle(void *object_ptr, double time) {

    Object *object = (Object *)object_ptr;

    float x0 = 0.0f, y0 = 0.4f;
    float x1 = -0.2f, y1 = -0.2f;
    float x2 = 0.2f, y2 = -0.2f;

    double angle = time * 0.25f;
    float c = (float)cos(angle);
    float s = (float)sin(angle);

    object->vertices[0].position.x = x0 * c - y0 * s;
    object->vertices[0].position.y = x0 * s + y0 * c;

    object->vertices[1].position.x = x1 * c - y1 * s;
    object->vertices[1].position.y = x1 * s + y1 * c;

    object->vertices[2].position.x = x2 * c - y2 * s;
    object->vertices[2].position.y = x2 * s + y2 * c;

}

Object *get_triangle_object(Triangle t) {
    Object *triangle = initialize_object();

    on_update(triangle, rotateTriangle);

    Vertex* top = initialize_vertex(vec2ToVec3(t.a), getColor().red);
    Vertex* bottom_right = initialize_vertex(vec2ToVec3(t.b), getColor().green);
    Vertex* bottom_left = initialize_vertex(vec2ToVec3(t.c), getColor().blue);

    add_vertex(triangle, top);
    add_vertex(triangle, bottom_right);
    add_vertex(triangle, bottom_left);
    return triangle;

}

Triangle init_triangle(vec2 a, vec2 b, vec2 c) {
    Triangle t;
    t.a = a;
    t.b = b;
    t.c = c;
    return t;
}