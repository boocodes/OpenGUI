#pragma once
#ifndef UTILS_H
#define UTILS_H
#include "./shader/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <stb_image.h>

unsigned int load_texture(const char* path);
GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram(const char* vertexSrc, const char* fragmentSrc);

unsigned int made_texture_png(const char* texture_path);
unsigned int made_texture_jpg(const char* texture_path);


#endif