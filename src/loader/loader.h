#pragma once
#ifndef LOADER_H
#define LOADER_H

#include <stb_image.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../general/shader/shader.h"
#include "../storage.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

void show_loader();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


#endif	