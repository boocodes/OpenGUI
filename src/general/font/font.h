#pragma once
#ifndef FONT_H
#define FONT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



typedef struct Character {
    unsigned int TextureID; // ID �������� �����
    glm::ivec2   Size;      // ������ �����
    glm::ivec2   Bearing;   // �������� �� ����� ������ �� ��������/������ ���� �����
    unsigned int Advance;   // �������� �� ���������� �����
};





#endif