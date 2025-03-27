#include "welcome_page.h"


int WIDTH = 773, HEIGHT = 628;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


unsigned int top_bar_VBO, top_bar_VAO;
unsigned int left_bar_VBO, left_bar_VAO;
unsigned int select_menu_active_item_decor_VBO, select_menu_active_item_decor_VAO;

unsigned int minimize_icon_VBO, minimize_icon_VAO;
unsigned int extend_icon_VBO, extend_icon_VAO;
unsigned int close_icon_VBO, close_icon_VAO;

unsigned int minimize_icon_texture;
unsigned int extend_icon_texture;
unsigned int close_icon_texture;

int select_menu_active_item = 0;


// Содержит всю информацию о состоянии символа, загруженному с помощью библиотеки FreeType
struct CharacterStruct {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2   Size;      // размер глифа
    glm::ivec2   Bearing;   // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance;   // смещение до следующего глифа
};

std::map<GLchar, CharacterStruct> Characters_list;
unsigned int text_VBO, text_VAO;


void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4  projection);

float top_bar_vertices[] = {
     1.0f, 1.0f, 0.0f,    0.16862745, 0.17647058, 0.18823529,
     1.0f, 0.85f, 0.0f,    0.16862745, 0.17647058, 0.18823529,
    -1.0f, 0.85f, 0.0f,    0.16862745, 0.17647058, 0.18823529,
    -1.0f, 1.0f, 0.0f,    0.16862745, 0.17647058, 0.18823529,
};

float left_bar_vertices[] = {
    -0.4f, 0.84f, 0.0f,   0.16862745, 0.17647058, 0.18823529,
    -0.4f, -1.0f, 0.0f,   0.16862745, 0.17647058, 0.18823529,
    -1.0f, -1.0f, 0.0f,   0.16862745, 0.17647058, 0.18823529,
    -1.0f, 0.84f, 0.0f,   0.16862745, 0.17647058, 0.18823529,
};
float select_menu_active_item_decor_vertices[] = {
    -0.40f, 0.72f, 0.0f,   0.18039215, 0.26274509, 0.43137254,
    -0.40f, 0.58f, 0.0f,   0.18039215, 0.26274509, 0.43137254,
    -0.97f, 0.58f, 0.0f,   0.18039215, 0.26274509, 0.43137254,
    -0.97f, 0.72f, 0.0f,   0.18039215, 0.26274509, 0.43137254,
};
float minimize_icon_vertices[] = {
    // координаты        // цвета            // текстурные координаты
         0.80f,  0.98f, 0.0f,   0.16862745f, 0.17647058f, 0.18823529f,   1.0f, 1.0f, // верхняя правая вершина
         0.80f,  0.88f, 0.0f,   0.16862745f, 0.17647058f, 0.18823529f,   1.0f, 0.0f, // нижняя правая вершина
         0.75f,  0.88f, 0.0f,   0.16862745f, 0.17647058f, 0.18823529f,   0.0f, 0.0f, // нижняя левая вершина
         0.75f,  0.98f, 0.0f,   0.16862745f, 0.17647058f, 0.18823529f,   0.0f, 1.0f  // верхняя левая вершина 
};
float extend_icon_vertices[] = {
    // координаты        // цвета            // текстурные координаты
         0.88f,  0.96f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   1.0f, 1.0f, // верхняя правая вершина
         0.88f,  0.90f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   1.0f, 0.0f, // нижняя правая вершина
         0.83f,  0.90f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   0.0f, 0.0f, // нижняя левая вершина
         0.83f,  0.96f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   0.0f, 1.0f  // верхняя левая вершина 
};
float close_icon_vertices[] = {
    // координаты        // цвета            // текстурные координаты
         0.96f,  0.97f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   1.0f, 1.0f, // верхняя правая вершина
         0.96f,  0.89f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   1.0f, 0.0f, // нижняя правая вершина
         0.90f,  0.89f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   0.0f, 0.0f, // нижняя левая вершина
         0.90f,  0.97f, 0.0f,   0.16862745, 0.17647058, 0.18823529,   0.0f, 1.0f  // верхняя левая вершина 
};



void show_welcome_page()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, false);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGUI", NULL, NULL);
    int max_width = GetSystemMetrics(SM_CXSCREEN);
    int max_hieght = GetSystemMetrics(SM_CYSCREEN);
    glfwSetWindowMonitor(window, NULL, (max_width / 2) - (WIDTH / 2), (max_hieght / 2) - (HEIGHT / 2), WIDTH, HEIGHT, GLFW_DONT_CARE);


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // -----FONT INIT-----

    Shader font_shader("src/main_app/shaders/font.vs", "src/main_app/shaders/font.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT));


    FT_Library ft;

    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // Путь к файлу шрифта
    std::string font_name = "assets/Roboto-Medium.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return;
    }
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    else {
        // Задаем размер для загрузки глифов
        FT_Set_Pixel_Sizes(face, 0, 48);

        // Отключаем ограничение выравнивания байтов
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Загружаем глифы символов 
        for (unsigned int c = 0; c < 256; c++)
        {
            // Загружаем глиф символа 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            // Генерируем текстуру
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            // Задаем для текстуры необходимые опции
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Теперь сохраняем символ для последующего использования
            CharacterStruct character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters_list.insert(std::pair<char, CharacterStruct>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &text_VAO);
    glGenBuffers(1, &text_VBO);
    glBindVertexArray(text_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // -----------

    // -------RIGHT BAR---------
    glGenVertexArrays(1, &top_bar_VAO);
    glGenBuffers(1, &top_bar_VBO);

    glBindVertexArray(top_bar_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, top_bar_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(top_bar_vertices), top_bar_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // --------------------
    // -----LEFT BAR-------
    glGenVertexArrays(1, &left_bar_VAO);
    glGenBuffers(1, &left_bar_VBO);

    glBindVertexArray(left_bar_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, left_bar_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(left_bar_vertices), left_bar_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader static_default("src/main_app/shaders/static_default.vs", "src/main_app/shaders/static_default.fs");
    // ---------------
    // -----ACTIVE SELECT ITEAM ------
    glGenVertexArrays(1, &select_menu_active_item_decor_VAO);
    glGenBuffers(1, &select_menu_active_item_decor_VBO);

    glBindVertexArray(select_menu_active_item_decor_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, select_menu_active_item_decor_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(select_menu_active_item_decor_vertices), select_menu_active_item_decor_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader static_situable("src/main_app/shaders/static_situable.vs", "src/main_app/shaders/static_situable.fs");
    // ---------------
    // ----MINIMIZE ICON--------

    Shader texture("src/main_app/shaders/texture.vs", "src/main_app/shaders/texture.fs");

    glGenVertexArrays(1, &minimize_icon_VAO);
    glGenBuffers(1, &minimize_icon_VBO);

    glBindVertexArray(minimize_icon_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, minimize_icon_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(minimize_icon_vertices), minimize_icon_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &minimize_icon_texture);
    glBindTexture(GL_TEXTURE_2D, minimize_icon_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Загрузка изображения, создание текстуры и генерирование мипмап-уровней
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load("assets/minimize.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //--- EXTEND ICON ------

    glGenVertexArrays(1, &extend_icon_VAO);
    glGenBuffers(1, &extend_icon_VBO);

    glBindVertexArray(extend_icon_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, extend_icon_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(extend_icon_vertices), extend_icon_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &extend_icon_texture);
    glBindTexture(GL_TEXTURE_2D, extend_icon_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Загрузка изображения, создание текстуры и генерирование мипмап-уровней

    data = stbi_load("assets/extend.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //-------------------------
    //------CLOSE ICON---------

    glGenVertexArrays(1, &close_icon_VAO);
    glGenBuffers(1, &close_icon_VBO);

    glBindVertexArray(close_icon_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, close_icon_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(close_icon_vertices), close_icon_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &close_icon_texture);
    glBindTexture(GL_TEXTURE_2D, close_icon_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Загрузка изображения, создание текстуры и генерирование мипмап-уровней

    data = stbi_load("assets/close.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(0.11764705f, 0.12156862f, 0.1333333f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        static_default.use();
        glBindVertexArray(top_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(left_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        static_situable.use();
        static_situable.setInt("active_elem", select_menu_active_item);
        glBindVertexArray(select_menu_active_item_decor_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        RenderText(font_shader, "OpenGUI", 25.0f, 599.0f, 0.4f, glm::vec3(0.41568627, 0.4235941, 0.44313725), projection);

        RenderText(font_shader, "Projects", 25.0f, 510.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f), projection);
        RenderText(font_shader, "Environment", 25.0f, 450.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f), projection);
        RenderText(font_shader, "Addons", 25.0f, 390.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f), projection);
        RenderText(font_shader, "Documentation", 25.0f, 330.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f), projection);


        // minimize, extend, close
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, minimize_icon_texture);
        texture.use();
        glBindVertexArray(minimize_icon_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(extend_icon_VAO);
        glBindTexture(GL_TEXTURE_2D, extend_icon_texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(close_icon_VAO);
        glBindTexture(GL_TEXTURE_2D, close_icon_texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        //-------


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
    return;
}

// Рендер строки текста
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4  projection)
{
    // Активируем соответствующее состояние рендеринга	
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_VAO);

    // Перебираем все символы
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        CharacterStruct ch = Characters_list[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        // Обновляем VBO для каждого символа
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // Рендерим текстуру глифа на прямоугольник
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // Обновляем содержимое памяти VBO
        glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Рендер прямоугольника
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Теперь производим смещение для отображения следующего глифа (обратите внимание, что данное смещение измеряется в единицах, составляющих 1/64 пикселя)
        x += (ch.Advance >> 6) * scale; // битовый сдвиг на 6 разрядов, чтобы получить значение в пикселях (2^6 = 64 (разделите количество 1/64-х пикселей на 64, чтобы получить количество пикселей))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glLoadIdentity();
}


void processInput(GLFWwindow* window)
{
    double mouse_x_pos, mouse_y_pos;
    glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        std::cout << mouse_x_pos << ", " << mouse_y_pos << std::endl;
    }
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}