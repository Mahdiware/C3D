//
// Created by arjun on 10/22/25.
//
#include <stdio.h>
#include "renderer.h"
#include "engine/core/shader/shader.h"
#include <stdlib.h>
#include "engine/object/object.h"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Renderer *__create_renderer() {
    Renderer *r = (Renderer *) malloc(sizeof(Renderer));
    r->width = 0;
    r->height = 0;
    r->initialized = 0;
    r->window = NULL;
    r->shaderProgram = 1;
    r->VAO = -1;
    r->VBO = -1;
    return r;
}

void destroy_renderer(Renderer *renderer) {
    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glDeleteProgram(renderer->shaderProgram);
    glfwDestroyWindow(renderer->window);
    glfwTerminate();
    free(renderer);
}
Renderer *init_renderer(int height, int width, char *title) {

    /*
     * INITIALIZE THE Renderer
     */
    Renderer *r = __create_renderer();

    /*
     * INITIALIZE OPENGL
     */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return r;


    /*
     * SET OPENGL VERSION
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /*
     * INITIALIZE OPENGL WINDOW
     */
    r->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!r->window) { glfwTerminate(); return r; }

    glfwMakeContextCurrent(r->window);
    glfwSetFramebufferSizeCallback(r->window, framebuffer_size_callback);

    /*
     * INITIALIZE OPENGL RENDERER
     */

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        r->initialized = 0;
        return r;
    }

    /*
     * INITIALIZE SHADER PROGRAM AND COMPILE SHADERS
     */
    r->shaderProgram = create_shader_program();
    glUseProgram(r->shaderProgram);


    // --------------------------
    // VAO/VBO setup
    // --------------------------

    glGenVertexArrays(1, &r->VAO);
    glGenBuffers(1, &r->VBO);
    glBindVertexArray(r->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
    glBufferData(GL_ARRAY_BUFFER, 4096 * sizeof(Vertex), 0, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    r->initialized = 1;
    return  r;
}

void renderer_polling(Renderer *r) {
    while (!glfwWindowShouldClose(r->window)) {
        glfwPollEvents();
        if (glfwGetKey(r->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(r->window, 1);

        glClearColor(0.1f,0.12f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        r->currentTime = glfwGetTime();
        glUseProgram(r->shaderProgram);
        glBindVertexArray(r->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, r->VAO);

        for (int i = 0; i < r->currentScene->totalObjects; i++) {
            Object *obj = &r->currentScene->objects[i];
            glBufferSubData(GL_ARRAY_BUFFER, 0, obj->total_vertices * sizeof(Vertex), obj->vertices);
            glDrawArrays(obj->mode, 0, obj->total_vertices);
        }

        glfwSwapBuffers(r->window);
    }
}