#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/renderer/renderer.h"
#include "math.h"
#include "engine/helper/helper.h"
#include "engine/triangle/Triangle.h"
#include "engine/vec2/vec2.h"
#include "engine/Line/line.h"

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

float rotationSpeed = 1;
matrix4x4 roxCubeZ(double time) {

    double thita = rotationSpeed * time;
    matrix4x4 mat = {0};
    mat.a[0][0] = cos(thita);
    mat.a[0][1] = sin(thita);

    mat.a[1][0] = -sin(thita);
    mat.a[1][1] = cos(thita);

    mat.a[2][2] = 1;
    mat.a[3][3] = 1;
    return mat;
}
matrix4x4 roxCubeX(double time) {
    double thita = rotationSpeed * time;
    matrix4x4 mat = {0};
    mat.a[0][0] = 1;
    mat.a[1][1] = cos(thita * 0.5);
    mat.a[1][2] = sin(thita * 0.5);

    mat.a[2][1] = -sin(thita * 0.5);
    mat.a[2][2] = cos(thita * 0.5);

    mat.a[3][3] = 1;
    return mat;
}

void rotateCube3d(void *mesh_p, double time) {
    Mesh *mesh = (Mesh *)mesh_p;

    for (int i = 0; i < mesh->num_objects; i++) {
        Object *obj = mesh->objects[i];

        for (int j = 0; j < obj->total_vertices; j ++) {
            vec3d rotatedZ = multiplyMatrix4x4AndVec3(obj->vertices[j].position, roxCubeZ(time));
            vec3d rotatedX = multiplyMatrix4x4AndVec3(fromVec3d(rotatedZ), roxCubeX(time));
            obj->vertices[j].position = fromVec3d(rotatedX);
        }
    }
}


Mesh *get3dCube() {
    Mesh *cube = initialize_mesh();

    // FRONT
    Mesh *front1 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 0}, (vec3){1, 1, 0}, (vec3){0,0,0}), (vec3 []){getColor().red}, 1);
    Mesh *front2 = get_triangle_object_line(init_triangle_3((vec3){1, 1, 0}, (vec3){0, 0, 0}, (vec3){1,0,0}), (vec3 []){getColor().red}, 1);
    add_objects(cube, front1->objects, front1->num_objects);
    add_objects(cube, front2->objects, front2->num_objects);

    // left
    Mesh *left1 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 1}, (vec3){0, 0, 1}, (vec3){0,0,0}), (vec3 []){getColor().red}, 1);
    Mesh *left2 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 1}, (vec3){0, 1, 0}, (vec3){0,0,0}), (vec3 []){getColor().red}, 1);
    add_objects(cube, left1->objects, left1->num_objects);
    add_objects(cube, left2->objects, left2->num_objects);


    // BACK
    Mesh *back1 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 1}, (vec3){0, 0, 1}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    Mesh *back2 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 1}, (vec3){1, 1, 1}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    add_objects(cube, back1->objects, back1->num_objects);
    add_objects(cube, back2->objects, back2->num_objects);

    // RIGHT
    Mesh *right1 = get_triangle_object_line(init_triangle_3((vec3){1, 1, 1}, (vec3){1,1,0}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    Mesh *right2 = get_triangle_object_line(init_triangle_3((vec3){1, 1, 0}, (vec3){1, 0, 0}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    add_objects(cube, right1->objects, right1->num_objects);
    add_objects(cube, right2->objects, right2->num_objects);


    // TOP
    Mesh *top1 = get_triangle_object_line(init_triangle_3((vec3){0, 1, 1}, (vec3){1,1,1}, (vec3){0,1,0}), (vec3 []){getColor().red}, 1);
    Mesh *top2 = get_triangle_object_line(init_triangle_3((vec3){1, 1, 1}, (vec3){1, 1, 0}, (vec3){0,1,0}), (vec3 []){getColor().red}, 1);
    add_objects(cube, top1->objects, top1->num_objects);
    add_objects(cube, top2->objects, top2->num_objects);


    // Bottom
    Mesh *bottom1 = get_triangle_object_line(init_triangle_3((vec3){0, 0, 0}, (vec3){0,0,1}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    Mesh *bottom2 = get_triangle_object_line(init_triangle_3((vec3){0, 0, 0}, (vec3){1, 0, 0}, (vec3){1,0,1}), (vec3 []){getColor().red}, 1);
    add_objects(cube, bottom1->objects, bottom1->num_objects);
    add_objects(cube, bottom2->objects, bottom2->num_objects);

    on_update_mesh(cube, rotateCube3d);
    // rotateCube3d(cube, 20);
    return cube;
}

int main(void) {
    Scene *scene =(Scene *) malloc(sizeof(Scene));
    Renderer *renderer = init_renderer(800, 800, "C 3d Rendering Engine");
    renderer->currentScene = scene;
    add_mesh(scene, get3dCube());
    // add_mesh(scene, createBasicTriangle2());
    renderer_polling(renderer);
    destroy_renderer(renderer);
    free(scene);
    return 0;
}
