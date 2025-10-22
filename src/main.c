#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/core/renderer/renderer.h"
#include "math.h"
#include "engine/triangle/Triangle.h"
#include "engine/vec2/vec2.h"


Object *createBasicTriangle() {
    Triangle triangle = init_triangle((vec2){0.0f, 0.5f}, (vec2){-0.5f, -0.5f}, (vec2){0.5f, -0.5f});
    return get_triangle_object(triangle);
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
