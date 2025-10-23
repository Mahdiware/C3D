//
// Created by arjun on 10/22/25.
//

#include "Triangle.h"

#include <stdio.h>
#include "math.h"
#include "engine/helper/helper.h"

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

Object *get_triangle_object_filled(Triangle t, vec3 *c, int colors) {
    Object *triangle = initialize_object();

    // on_update(triangle, rotateTriangle);
    // triangle->mode = GL_LINES;

    vec3 mainColor = getColor().red;

    if (colors > 0) {
        mainColor = c[0];
    }

    vec3 c1 = mainColor;
    vec3 c2= mainColor;
    vec3 c3= mainColor;

    if (colors >= 2) {
        c2 = c[1];
    }

    if (colors == 3) {
        c3 = c[2];
    }
    Vertex* top = initialize_vertex((t.a), c1);
    Vertex* bottom_right = initialize_vertex((t.b), c2);
    Vertex* bottom_left = initialize_vertex((t.c), c3);

    add_vertex(triangle, top);
    add_vertex(triangle, bottom_right);
    add_vertex(triangle, bottom_left);
    return triangle;
}
Triangle from_vertices(Vertex *verticies, int num_vertices) {
    Triangle triangle = init_triangle_3(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
    if (num_vertices != 3) {
        printf("Error: The verticies isnt a triangle ");
    }
    triangle.a = verticies[0].position;
    triangle.b = verticies[1].position;
    triangle.c = verticies[2].position;
    return triangle;
}

Triangle init_triangle(vec2 a, vec2 b, vec2 c) {
    Triangle t;
    t.a = vec2ToVec3(a);
    t.b = vec2ToVec3(b);
    t.c = vec2ToVec3(c);
    return t;
}
Triangle init_triangle_3(vec3 a, vec3 b, vec3 c) {
    Triangle t;
    t.a = (a);
    t.b = (b);
    t.c = (c);
    return t;
}
vec3 getNormalVector(Triangle t) {
    vec3 line1 = {0, 0, 0};
    line1.x = t.b.x - t.a.x;
    line1.y = t.b.y - t.a.y;
    line1.z = t.b.z - t.a.z;

    vec3 line2 = {0, 0, 0};
    line2.x = t.c.x - t.a.x;
    line2.y = t.c.y - t.a.y;
    line2.z = t.c.z - t.a.z;

    vec3 normalized = {0, 0, 0};
    normalized.x = line1.y * line2.z - line1.z * line2.y;
    normalized.y = line1.z * line2.x - line1.x * line2.z;
    normalized.z = line1.x * line2.y - line1.y * line2.x;

    float l = sqrtf(normalized.x * normalized.x + normalized.y * normalized.y + normalized.z * normalized.z);
    normalized.x /= l;
    normalized.y /= l;
    normalized.z /= l;

    return normalized;
}