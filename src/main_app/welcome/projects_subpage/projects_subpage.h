#pragma once
#ifndef PROJECTS_SUBPAGE_H
#define PROJECTS_SUBPAGE_H
#include "../../../general/shader/shader.h";
#include <iostream>
#include "../../../general/font/font.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Projects_subpage {
private:
	std::vector<Shader> shader_list;
	std::vector<Font> font_list;
	std::vector<unsigned int> VAO_list;
	std::vector<glm::mat4> projection_list;
	int SCR_WIDTH;
	int SCR_HEIGHT;
public:
	Projects_subpage(int SCR_WIDTH, int SCR_HEIGHT);
	void show_project_subpage();
	void init();
};



#endif // !PROJECTS_SUBPAGE_H
