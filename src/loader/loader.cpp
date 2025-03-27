#include "loader.h"


const int WIDTH = 836;
const int HEIGHT = 600;

float loader_line_progress_bar = 0.0;
std::string loader_line_progress_bar_text = "Loading";

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

float loader_line_progress_bar_vertices[] = {
         0.5f, -0.92f,  0.0f,  0.14117647, 0.38431372, 0.65882352,
         0.5f, -0.94f, 0.0f,  0.14117647, 0.38431372, 0.65882352,
        -0.5f, -0.94f, 0.0f,  0.14117647, 0.38431372, 0.65882352,
        -0.5f, -0.92f,  0.0f,  0.14117647, 0.38431372, 0.65882352,
};

void progres_bar_tick()
{

    if (loader_line_progress_bar == 0.0f)
    {
        loader_line_progress_bar_text = "Project compilation";
    }
    else if (loader_line_progress_bar == 0.2f)
    {
        loader_line_progress_bar_text = "Shader initiliaziation";
    }
    else if (loader_line_progress_bar == 0.4f)
    {
        loader_line_progress_bar_text = "Shader compilation";
    }
    else if (loader_line_progress_bar == 0.6f)
    {
        loader_line_progress_bar_text = "Connecting to server";
    }
    else if (loader_line_progress_bar == 0.8f)
    {
        loader_line_progress_bar_text = "Info collection";
    }
    else if (loader_line_progress_bar == 1.0f)
    {
        loader_line_progress_bar_text = "Final prepare";
    }
    Sleep(500);
    loader_line_progress_bar += 0.20;
    Sleep(300);
    
}


// Содержит всю информацию о состоянии символа, загруженному с помощью библиотеки FreeType
struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2   Size;      // размер глифа
    glm::ivec2   Bearing;   // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance;   // смещение до следующего глифа
};

std::map<GLchar, Character> Characters;
unsigned int font_VAO, font_VBO;


void show_loader()          
{
    // glfw: инициализация и конфигурирование
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
   

    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    

   
    Shader font_shader("src/loader/font.vs", "src/loader/font.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), 0.0f, static_cast<float>(HEIGHT));
    

    Shader background_shader("src/loader/loader.vs", "src/loader/loader.fs");

    FT_Library ft;

    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // Путь к файлу шрифта
    std::string font_name = "assets/Roboto-Bold.ttf";
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
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &font_VAO);
    glGenBuffers(1, &font_VBO);
    glBindVertexArray(font_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, font_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Указывание вершин (и буферов) и настройка вершинных атрибутов
    float background_vertices[] = {
        // координаты        // цвета            // текстурные координаты
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // верхняя правая вершина
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижняя правая вершина
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // нижняя левая вершина
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // верхняя левая вершина 
    };
    unsigned int background_indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    float loader_line_back_vertices[] = {
         1.0f, -0.92f, 0.0f,   1.0f, 1.0f, 1.0f,
         1.0f, -0.94f, 0.0f,   1.0f, 1.0f, 1.0f,
        -1.0f, -0.94f, 0.0f,   1.0f, 1.0f, 1.0f,
        -1.0f, -0.92f, 0.0f,   1.0f, 1.0f, 1.0f,
    };

    
    

    unsigned int background_VBO, background_VAO, background_EBO;
    glGenVertexArrays(1, &background_VAO);
    glGenBuffers(1, &background_VBO);
    glGenBuffers(1, &background_EBO);


    glBindVertexArray(background_VAO);


    glBindBuffer(GL_ARRAY_BUFFER, background_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(background_vertices), background_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, background_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(background_indices), background_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

   

    unsigned int background_texture;
    glGenTextures(1, &background_texture);
    glBindTexture(GL_TEXTURE_2D, background_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/loaderp.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

   
    Shader shader_line("src/loader/loader_line.vs", "src/loader/loader_line.fs");

    unsigned int loader_line_back_VBO, loader_line_back_VAO;

    glGenVertexArrays(1, &loader_line_back_VAO);
    glGenBuffers(1, &loader_line_back_VBO);
    
    glBindVertexArray(loader_line_back_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, loader_line_back_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(loader_line_back_vertices), loader_line_back_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int loader_line_progress_bar_VBO, loader_line_progress_bar_VAO;

    glGenVertexArrays(1, &loader_line_progress_bar_VAO);
    glGenBuffers(1, &loader_line_progress_bar_VBO);

    glBindVertexArray(loader_line_progress_bar_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, loader_line_progress_bar_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(loader_line_progress_bar_vertices), loader_line_progress_bar_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader progress_bar("src/loader/progress_bar.vs", "src/loader/progress_bar.fs");

    
    


    while (!glfwWindowShouldClose(window))
    {
       
        if (loader_line_progress_bar == 1.0) break;
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, background_texture);
        background_shader.use();
        glBindVertexArray(background_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shader_line.use();
        glBindVertexArray(loader_line_back_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        progress_bar.use();
        progress_bar.setFloat("progres", loader_line_progress_bar);
        
        glBindVertexArray(loader_line_progress_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        

        // Состояние OpenGL
        font_shader.use();
        glUniformMatrix4fv(glGetUniformLocation(font_shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        RenderText(font_shader, "OpenGUI", 72.0f, 500.0f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f));
        RenderText(font_shader, "2025.0.1", 72.0f, 470.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
        RenderText(font_shader, loader_line_progress_bar_text, 72.0f, 40.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
        glLoadIdentity();
        

        progres_bar_tick();
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }



    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
    return;
}


// Рендер строки текста
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // Активируем соответствующее состояние рендеринга	
    
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font_VAO);

    // Перебираем все символы
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

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
        glBindBuffer(GL_ARRAY_BUFFER, font_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Рендер прямоугольника
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Теперь производим смещение для отображения следующего глифа (обратите внимание, что данное смещение измеряется в единицах, составляющих 1/64 пикселя)
        x += (ch.Advance >> 6) * scale; // битовый сдвиг на 6 разрядов, чтобы получить значение в пикселях (2^6 = 64 (разделите количество 1/64-х пикселей на 64, чтобы получить количество пикселей))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}