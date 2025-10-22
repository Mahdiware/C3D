//
// Created by arjun on 10/22/25.
//

#ifndef C_3D_RENDERING_ENGINE_SHADER_H
#define C_3D_RENDERING_ENGINE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint compile_shader(GLenum type, const char* source);
GLuint create_shader_program();

#endif //C_3D_RENDERING_ENGINE_SHADER_H