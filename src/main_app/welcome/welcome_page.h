#ifndef WELCOME_PAGE_H
#define WELCOME_PAGE_H


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../general/shader/shader.h"
#include "../../general/utils.h"
#include "../../general/font/font.h"
#include "./projects_subpage/projects_subpage.h"


#include <ft2build.h>
#include FT_FREETYPE_H

void show_welcome_page();


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4  projection);



#endif // WELCOME_PAGE_H
