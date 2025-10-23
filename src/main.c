#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/renderer/renderer.h"
#include "math.h"
#include "engine/helper/helper.h"
#include "engine/triangle/Triangle.h"
#include "engine/vec2/vec2.h"
#include "engine/matrix4x4/matrix4x4.h"
#include "engine/Mesh/mesh.h"
#include "engine/Rect/Rect.h"
#include "engine/vec3/vec3.h"
#include "engine/object/object.h"

// Mesh *createBasicTriangle() {
//     Triangle triangle = init_triangle((vec2){1.0f, 2.0f}, (vec2){0.0f, 0.0f}, (vec2){2.0f, 0.0f});
//     Mesh *mesh = initialize_mesh();
//     add_object(mesh,get_triangle_object_filled(triangle, (vec3 []){getColor().red}, 1) );
//     return mesh;
// }

// Mesh *createBasicTriangle() {
//     Triangle triangle = init_triangle((vec2){1.0f, 2.0f}, (vec2){0.0f, 0.0f}, (vec2){2.0f, 0.0f});
//     return get_triangle_object_line(triangle, (vec3 []){getColor().red}, 1);
// }
//
// Mesh *createBasicTriangle2() {
//     Triangle triangle = init_triangle((vec2){1.0f, 2.0f}, (vec2){3.0f, 2.0f}, (vec2){2.0f, 0.0f});
//     return get_triangle_object_line(triangle, (vec3 []){getColor().red}, 1);
// }
//
// Mesh *createLine() {
//     Line *line = init_line((vec3){0.0f, 0.0f, 1.0f}, (vec3){10.0f, 10.0f, 1.0f});
//     return get_line_mesh(line);
// }
typedef struct {
    vec3d *base_positions;
    int count;
} MeshRotationData;

float rotationSpeed = 1.0f;

matrix4x4 rotZ(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = cos(angle);
    m.a[0][1] = sin(angle);
    m.a[1][0] = -sin(angle);
    m.a[1][1] = cos(angle);
    m.a[2][2] = 1;
    m.a[3][3] = 1;
    return m;
}

matrix4x4 rotX(double angle) {
    matrix4x4 m = {0};
    m.a[0][0] = 1;
    m.a[1][1] = cos(angle);
    m.a[1][2] = -sin(angle);
    m.a[2][1] = sin(angle);
    m.a[2][2] = cos(angle);
    m.a[3][3] = 1;
    return m;
}

void rotateCube3d(void *mesh_p, double time) {
    Mesh *mesh = (Mesh *)mesh_p;

    double angle = rotationSpeed * time;
    matrix4x4 rotZMat = rotZ(angle);
    matrix4x4 rotXMat = rotX(angle * 0.5);

    vec3 center = {0.5f, 0.5f, 0.5f}; // cube center (since coordinates are 0–1)

    for (int i = 0; i < mesh->num_objects; i++) {
        Object *obj = mesh->objects[i];

        for (int j = 0; j < obj->total_vertices; j++) {
            vec3 pos = obj->vertices[j].position;

            // Translate to center
            pos.x -= center.x;
            pos.y -= center.y;
            pos.z -= center.z;

            // Rotate
            vec3d temp = multiplyMatrix4x4AndVec3(pos, rotZMat);
            vec3d rotated = multiplyMatrix4x4AndVec3(fromVec3d(temp), rotXMat);

            // Translate back
            obj->vertices[j].position.x = rotated.x + center.x;
            obj->vertices[j].position.y = rotated.y + center.y;
            obj->vertices[j].position.z = rotated.z + center.z;
        }
    }
}


//
// void rotateCube3d(void *mesh_p, double time) {
//     Mesh *mesh = (Mesh *)mesh_p;
//     double angleZ = time * rotationSpeed;
//     double angleX = time * rotationSpeed * 0.7; // a bit different for depth feel
//
//     // rotation matrices
//     matrix4x4 rotZ = roxCubeZ(angleZ);
//     matrix4x4 rotX = roxCubeX(angleX);
//
//     // combine rotations: rotZ * rotX
//     matrix4x4 rotCombined = multiplyMatrix4x4(rotZ, rotX);
//
//     // optional: rotation center offset
//     vec3 center = {0.5f, 0.5f, 0.5f};
//
//     for (int i = 0; i < mesh->num_objects; i++) {
//         Object *obj = mesh->objects[i];
//         for (int j = 0; j < obj->total_vertices; j++) {
//             // shift to origin
//             vec3 pos = obj->vertices[j].position;
//             pos.x -= center.x;
//             pos.y -= center.y;
//             pos.z -= center.z;
//
//             // apply rotation
//             vec3d rotated = multiplyMatrix4x4AndVec3(pos, rotCombined);
//
//             // shift back
//             rotated.x += center.x;
//             rotated.y += center.y;
//             rotated.z += center.z;
//
//             obj->vertices[j].position = fromVec3d(rotated);
//         }
//     }
// }
Mesh *get3dCube() {
    Mesh *cube = initialize_mesh();

    Color colors = getColor(); // Avoid calling repeatedly

    // FRONT (Z = 0)
    Mesh *front = get_rect_mesh(
        init_rect(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(1, 1, 0), Vec3(1, 0, 0)),
        (vec3[]){colors.green}, 1);
    add_objects(cube, front->objects, front->num_objects);

    // LEFT (X = 0)
    Mesh *left = get_rect_mesh(
        init_rect(Vec3(0, 0, 1), Vec3(0, 1, 1), Vec3(0, 1, 0), Vec3(0, 0, 0)),
        (vec3[]){colors.cyan}, 1);
    add_objects(cube, left->objects, left->num_objects);

    // BACK (Z = 1)
    Mesh *back = get_rect_mesh(
        init_rect(Vec3(1, 0, 1), Vec3(1, 1, 1), Vec3(0, 1, 1), Vec3(0, 0, 1)),
        (vec3[]){colors.orange}, 1);
    add_objects(cube, back->objects, back->num_objects);

    // RIGHT (X = 1)
    Mesh *right = get_rect_mesh(
        init_rect(Vec3(1, 0, 0), Vec3(1, 1, 0), Vec3(1, 1, 1), Vec3(1, 0, 1)),
        (vec3[]){colors.white}, 1);
    add_objects(cube, right->objects, right->num_objects);

    // TOP (Y = 1)
    Mesh *top = get_rect_mesh(
        init_rect(Vec3(0, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 1), Vec3(1, 1, 0)),
        (vec3[]){colors.red}, 1);
    add_objects(cube, top->objects, top->num_objects);

    // BOTTOM (Y = 0)
    Mesh *bottom = get_rect_mesh(
        init_rect(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(1, 0, 1)),
        (vec3[]){colors.blue}, 1);
    add_objects(cube, bottom->objects, bottom->num_objects);

    // Rotation hook
    on_update_mesh(cube, rotateCube3d);



    return cube;
}

Mesh* get_Ship() {
    Mesh *ship = load_from_file("/home/arjun/c_3d_rendering_engine/VideoShip.obj");
    on_update_mesh(ship, rotateCube3d);
    return  ship;
}
int main(void) {
    Scene *scene =(Scene *) malloc(sizeof(Scene));
    //
    Renderer *renderer = init_renderer(800, 800, "C 3d Rendering Engine");
    renderer->currentScene = scene;
    add_mesh(scene, get_Ship());
    add_mesh(scene, get3dCube());
    renderer_polling(renderer);
    destroy_renderer(renderer);
    free(scene);

    return 0;
}
