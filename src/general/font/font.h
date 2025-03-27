#pragma once
#ifndef FONT_H
#define FONT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



typedef struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2   Size;      // размер глифа
    glm::ivec2   Bearing;   // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance;   // смещение до следующего глифа
};





#endif