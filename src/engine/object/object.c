//
// Created by arjun on 10/22/25.
//

#include "object.h"

#include <math.h>

#include "engine/helper/helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "engine/triangle/Triangle.h"
vec3 Camera  = {0, 0, 0};
vec3 Light = {0, 0, -1};
void noUpdate(void *k,double d) {
    // printf("NoUpdate\n");
}
Object *initialize_object() {
    Object *object = malloc(sizeof(Object));
    object->total_vertices = 0;
    object->vertices = NULL;
    object->update = noUpdate;
    return object;
}
void add_vertex(Object *object, Vertex *vertex) {
    object->vertices = realloc(object->vertices, sizeof(Vertex) * (object->total_vertices + 1));
    if (!object->vertices) {
        object->total_vertices = 0;
        return;
    }
    // Copy the new vertex into the array
    object->vertices[object->total_vertices] = *vertex;
    object->total_vertices++;
}

void remove_vertex(Object *object, Vertex *vertex) {
    if (!object || object->total_vertices == 0) return;

    int found_index = -1;
    for (int i = 0; i < object->total_vertices; i++) {
        if (memcmp(&object->vertices[i], vertex, sizeof(Vertex)) == 0) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1) return;
    for (int i = found_index; i < object->total_vertices - 1; i++) {
        object->vertices[i] = object->vertices[i + 1];
    }

    object->total_vertices--;
    if (object->total_vertices > 0) {
        object->vertices = realloc(object->vertices, sizeof(Vertex) * object->total_vertices);
    } else {
        free(object->vertices);
        object->vertices = NULL;
    }
}

void on_update(Object *object, update_function update) {
    object->update = update;
}

int printed = 3;
VertexArray get_vertex_screen(Object *obj, matrix4x4 projection, int height, int width) {
    Vertex *new_vertices = malloc(sizeof(Vertex) * obj->total_vertices);
    // printf("Number of vertices: %d\n", obj->total_vertices);
    for (int i = 0; i < obj->total_vertices; i++) {
        Vertex *vertex = &obj->vertices[i];
        new_vertices[i] = *vertex;
        new_vertices[i].position.z += 5.0f;
    }
    Triangle triangle = from_vertices(new_vertices, obj->total_vertices);

    vec3 normal = getNormalVector(triangle);
    float projected_visibility = normal.x * (triangle.a.x - Camera.x) +
                                normal.y * (triangle.a.y - Camera.y) +
                                    normal.z * (triangle.a.z - Camera.z);

    if (projected_visibility > 0) {
        return (VertexArray){new_vertices, 0};
    }
    float l = sqrt(Light.x * Light.x + Light.y * Light.y + Light.z * Light.z);
    Light.x /= l;
    Light.y /= l;
    Light.z /= l;

    float dp_light = ( normal.x * (Light.x) +
                            normal.y * (Light.y) +
                                normal.z * (Light.z));
    // apply_luminance(obj, dp_light);
    for (int i = 0; i < obj->total_vertices; i++) {
        Vertex *vertex = &obj->vertices[i];
        new_vertices[i] = *vertex;
        new_vertices[i].position.z += 5.0f;

        vec3 color = color_with_luminance(vertex->color, dp_light);

        vec3d current_pos = multiplyMatrix4x4AndVec3(new_vertices[i].position, projection);
        // current_pos.x += 1.0f;
        // current_pos.y += 1.0f;
        //
        // current_pos.x *= (0.5f * (float)width);
        // current_pos.y *= (0.5f * (float)height);
        // vec2 new_scr = screen_to_ndc(current_pos.x, current_pos.y, width, height);
        // current_pos.x = new_scr.x;
        // current_pos.y = new_scr.y;

        if (printed) {
            printf("Original vertex %d: {%.2f, %.2f, %.2f}\n", i, vertex->position.x, vertex->position.y, vertex->position.z);

            printf("new vertext %d{%.2f, %.2f, %.2f}\n", i, current_pos.x, current_pos.y, current_pos.z);
            printed--;
        }
        new_vertices[i].position = (vec3){current_pos.x, current_pos.y, current_pos.z};
        new_vertices[i].color = color;
    }
    return (VertexArray){new_vertices, 1};
}