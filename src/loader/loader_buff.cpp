//#include "loader.h"
//#include <Windows.h>
//
//std::string title = "OpenGUI";
//std::string current_version = "2025.0.1";
//int HEIGHT = 420;
//int WIDTH = 630;
//
//
//// Содержит всю информацию о состоянии символа, загруженному с помощью библиотеки FreeType
//struct Character {
//    unsigned int TextureID; // ID текстуры глифа
//    glm::ivec2   Size;      // размер глифа
//    glm::ivec2   Bearing;   // смещение от линии шрифта до верхнего/левого угла глифа
//    unsigned int Advance;   // смещение до следующего глифа
//};
//
//std::map<GLchar, Character> Characters;
//
//void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
//unsigned int VBO, VAO, EBO;
//void show_loader()
//{
//
//    // glfw: инициализация и конфигурирование    
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    glfwWindowHint(GLFW_DECORATED, 0);
//    // glfw: создание окна
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Welcome OpenGUI", NULL, NULL);
//    if (window == NULL)
//    {
//        glfwTerminate();
//        return;
//    }
//    glfwMakeContextCurrent(window);
//    int max_width = GetSystemMetrics(SM_CXSCREEN);
//    int max_hieght = GetSystemMetrics(SM_CYSCREEN);
//    glfwSetWindowMonitor(window, NULL, (max_width / 2) - (WIDTH / 2), (max_hieght / 2) - (HEIGHT / 2), WIDTH, HEIGHT, GLFW_DONT_CARE);
//
//    // glad: загрузка всех указателей на OpenGL-функции
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        return;
//    }
//    // Состояние OpenGL
//
//    Shader shader("src/loader/font.vs", "src/loader/font.fs");
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT));
//
//    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//
//    FT_Library ft;
//
//    if (FT_Init_FreeType(&ft))
//    {
//        return;
//    }
//    std::string font_name_bold = "assets/Roboto-Bold.ttf";
//    std::string font_name_medium = "assets/Roboto-Medium.ttf";
//    if (font_name_bold.empty() || font_name_medium.empty())
//    {
//        return;
//    }
//    FT_Face face_bold;
//    if (FT_New_Face(ft, font_name_bold.c_str(), 0, &face_bold))
//    {
//        return;
//    }
//    else
//    {
//        FT_Set_Pixel_Sizes(face_bold, 0, 40);
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//        for (unsigned int c = 0; c < 256; c++)
//        {
//            if (FT_Load_Char(face_bold, c, FT_LOAD_RENDER))
//            {
//                continue;
//            }
//            unsigned int texture;
//            glGenTextures(1, &texture);
//            glTexImage2D(
//                GL_TEXTURE_2D,
//                0,
//                GL_RED,
//                face_bold->glyph->bitmap.width,
//                face_bold->glyph->bitmap.rows,
//                0,
//                GL_RED,
//                GL_UNSIGNED_BYTE,
//                face_bold->glyph->bitmap.buffer
//            );
//
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            Character character = {
//                texture,
//                glm::ivec2(face_bold->glyph->bitmap.width, face_bold->glyph->bitmap.rows),
//                glm::ivec2(face_bold->glyph->bitmap_left, face_bold->glyph->bitmap_top),
//                static_cast<unsigned int>(face_bold->glyph->advance.x)
//            };
//            Characters.insert(std::pair<char, Character>(c, character));
//        }
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }
//
//    FT_Done_Face(face_bold);
//    FT_Done_FreeType(ft);
//
//
//    // Компилирование нашей шейдерной программы
//    Shader ourShader("src/loader/loader.vs", "src/loader/loader.fs");
//
//    // Указание вершин (и буфера(ов)) и настройка вершинных атрибутов
//    float vertices[] = {
//        // координаты        // цвета            // текстурные координаты
//        -1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // верхняя правая вершина
//        1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
//       1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // нижняя левая вершина
//       -1.0f,  -1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // верхняя левая вершина 
//    };
//    unsigned int indices[] = {
//        0, 1, 3, // первый треугольник
//        1, 2, 3  // второй треугольник
//    };
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // Координатные атрибуты
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Цветовые атрибуты
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    // Атрибуты текстурных координат
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    // Загрузка и создание текстуры
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект
//
//    // Установка параметров наложения текстуры
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//    // Установка параметров фильтрации текстуры
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    // Загрузка изображения, создание текстуры и генерирование мипмап-уровней
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load("assets/loaderp.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        return;
//    }
//    stbi_image_free(data);
//
//
//    // Устанавливаем вручную…
//    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//    // …или с помощью шейдерного класса
//    ourShader.setInt("texture2", 1);
//
//
//    // Цикл рендеринга
//    while (!glfwWindowShouldClose(window))
//    {
//
//
//        // Рендеринг
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // Связывание текстуры
//        glBindTexture(GL_TEXTURE_2D, texture);
//
//        // Рендеринг ящика
//        ourShader.use();
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Опционально: освобождаем все ресурсы, как только они выполнили свое предназначение
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//
//    // glfw: завершение, освобождение всех выделенных ранее GLFW-реурсов
//    glfwTerminate();
//    return;
//}
//
//
//
//// Рендер строки текста
//void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
//{
//    // Активируем соответствующее состояние рендеринга	
//    shader.use();
//    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);
//
//    // Перебираем все символы
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        Character ch = Characters[*c];
//
//        float xpos = x + ch.Bearing.x * scale;
//        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        float w = ch.Size.x * scale;
//        float h = ch.Size.y * scale;
//
//        // Обновляем VBO для каждого символа
//        float vertices[6][4] = {
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos,     ypos,       0.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//            { xpos + w, ypos + h,   1.0f, 0.0f }
//        };
//
//        // Рендерим текстуру глифа на прямоугольник
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//
//        // Обновляем содержимое памяти VBO
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        // Рендер прямоугольника
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        // Теперь производим смещение для отображения следующего глифа (обратите внимание, что данное смещение измеряется в единицах, составляющих 1/64 пикселя)
//        x += (ch.Advance >> 6) * scale; // битовый сдвиг на 6 разрядов, чтобы получить значение в пикселях (2^6 = 64 (разделите количество 1/64-х пикселей на 64, чтобы получить количество пикселей))
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}