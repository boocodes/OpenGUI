#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include "glad/glad.h"




class Object {
public:
	unsigned int VAO, VBO, EBO;
	Object(float* vertices);
	Object(float* vertices, float* indices);
	void draw();
};




#endif