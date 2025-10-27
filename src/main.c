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

Renderer *renderer;
double lastX = 0, lastY = 0;
float yaw = 0.0f, pitch = 0.0f;
int firstMouse = 1;
float sensitivity = 0.03f;
int mouseMoved = 0;
float rotationSpeed = 1.0f;

int invertYaw = 1;
int invertPitch = 1;

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

void rotateCube3d(void *mesh_p, double time) {
    Mesh *mesh = (Mesh *)mesh_p;
    if (!mesh) return;

    double autoAngle = 0.0;

    matrix4x4 rotZMat = rotZ(autoAngle);
    matrix4x4 rotXMat = rotX(autoAngle * 0.5);

    // Mouse rotation still applied if mouse moved
    matrix4x4 mouseYRot = rotY(mouseMoved ? yaw * (M_PI / 180.0) : 0);
    matrix4x4 mouseXRot = rotX(mouseMoved ? pitch * (M_PI / 180.0) : 0);

    matrix4x4 combined = multiplyMatrix4x4(mouseYRot, mouseXRot);
    combined = multiplyMatrix4x4(combined, rotZMat);
    combined = multiplyMatrix4x4(combined, rotXMat);

    vec3 center = {0.5f, 0.5f, 0.5f};

    for (int i = 0; i < mesh->num_objects; i++) {
        Object *obj = mesh->objects[i];
        for (int j = 0; j < obj->total_vertices; j++) {
            vec3 pos = obj->vertices[j].position;
            pos.x -= center.x;
            pos.y -= center.y;
            pos.z -= center.z;

            vec3d rotated = multiplyMatrix4x4AndVec3(pos, combined);

            obj->vertices[j].position.x = rotated.x + center.x;
            obj->vertices[j].position.y = rotated.y + center.y;
            obj->vertices[j].position.z = rotated.z + center.z;
        }
    }
}

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
        return;
    }

    mouseMoved = 1;

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (invertYaw)  xoffset = -xoffset;
    if (invertPitch) yoffset = -yoffset;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    vec3 front;
    front.x = cos(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);
    front.y = sin(pitch * M_PI / 180.0);
    front.z = sin(yaw * M_PI / 180.0) * cos(pitch * M_PI / 180.0);

    normalizeVec3(&front);
    copyVec3(&renderer->cameraFront, &front);
}

Mesh* get_Ship() {
    Mesh *ship = load_from_file("/home/mahdiware/Projects/C3D/VideoShip.obj");
    on_update_mesh(ship, rotateCube3d);
    return  ship;
}

Mesh* getTeapot() {
    Mesh *ship = load_from_file("/home/mahdiware/Projects/C3D/teapot.obj");
    on_update_mesh(ship, rotateCube3d);
    return  ship;
}

Mesh* getAxis() {
    Mesh *ship = load_from_file("/home/mahdiware/Projects/C3D/axis.obj");
    on_update_mesh(ship, rotateCube3d);
    return  ship;
}

int main(void) {
    Scene *scene =(Scene *) malloc(sizeof(Scene));
    //
    renderer = init_renderer(800, 800, "C 3d Rendering Engine");
    renderer->currentScene = scene;

    glfwSetCursorPosCallback(renderer->window, mouse_callback);
    glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    add_mesh(scene, get_Ship());
    add_mesh(scene, getTeapot());
    renderer_polling(renderer);
    destroy_renderer(renderer);
    free(scene);

    return 0;
}
