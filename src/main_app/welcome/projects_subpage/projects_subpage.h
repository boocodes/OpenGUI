#pragma once
#ifndef PROJECTS_SUBPAGE_H
#define PROJECTS_SUBPAGE_H
#include "../../../general/shader/shader.h";
#include <iostream>
#include <glad/glad.h>
#include <vector>

class Projects_subpage {
private:
	std::vector<Shader> shader_list;
public:
	Projects_subpage();
};



#endif // !PROJECTS_SUBPAGE_H
