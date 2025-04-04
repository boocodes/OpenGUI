#pragma once
#ifndef FONT_H
#define FONT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <glad/glad.h>
#include "../shader/shader.h"
#include <string>
#include <vector>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

struct CharacterStruct {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};



class Font {
private:
    std::map<GLchar, CharacterStruct> Characters_list;
    unsigned int text_VBO, text_VAO;
    const char* font_name;
    float scale;
    glm::vec3 color;
    int SCR_WIDTH;
    int SCR_HEIGHT;
    glm::mat4 font_projection;
    std::vector<Shader> shader_list;
public:
    float get_scale();
    void set_color(glm::vec3 color_vec);
    void set_scale(float scale_size);
    Font(const char* font_name, int SCR_WIDTH, int SCR_HEIGHT);
    void RenderText(std::string text, float x, float y);
    void init();
};


#endif // !FONT_H
