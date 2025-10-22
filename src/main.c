#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/renderer/renderer.h"

Object *createBasicTriangle() {
    Object *obj = initialize_object();

    Vertex* top = initialize_vertex( 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f);
    Vertex* bottom_right = initialize_vertex( -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
    Vertex* bottom_left = initialize_vertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f);

    add_vertex(obj, top);
    add_vertex(obj, bottom_right);
    add_vertex(obj, bottom_left);
    return obj;
}

int main(void) {
    Scene *scene =(Scene *) malloc(sizeof(Scene));
    Renderer *renderer = init_renderer(800, 600, "C 3d Rendering Engine");
    renderer->currentScene = scene;
    add_object(scene, createBasicTriangle());
    renderer_polling(renderer);
    destroy_renderer(renderer);
    free(scene);
    return 0;
}
