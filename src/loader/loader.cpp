#include "loader.h"


const int WIDTH = 836;
const int HEIGHT = 600;

float loader_line_progress_bar = 0.0;



float loader_line_progress_bar_vertices[] = {
         0.5f, -0.9f,  0.0f,  0.14117647, 0.38431372, 0.65882352,
         0.5f, -0.92f, 0.0f,  0.14117647, 0.38431372, 0.65882352,
        -0.5f, -0.92f, 0.0f,  0.14117647, 0.38431372, 0.65882352,
        -0.5f, -0.9f,  0.0f,  0.14117647, 0.38431372, 0.65882352,
};

void progres_bar_tick()
{
    // step 1
    loader_line_progress_bar += 0.20;
    Sleep(500);
    
}


void show_loader()          
{
    // glfw: инициализаци€ и конфигурирование
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

   
    Shader background_shader("src/loader/loader.vs", "src/loader/loader.fs");



    // ”казывание вершин (и буферов) и настройка вершинных атрибутов
    float background_vertices[] = {
        // координаты        // цвета            // текстурные координаты
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // верхн€€ права€ вершина
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // нижн€€ права€ вершина
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // нижн€€ лева€ вершина
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // верхн€€ лева€ вершина 
    };
    unsigned int background_indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    float loader_line_back_vertices[] = {
         1.0f, -0.9f, 0.0f,   1.0f, 1.0f, 1.0f,
         1.0f, -0.92f, 0.0f,   1.0f, 1.0f, 1.0f,
        -1.0f, -0.92f, 0.0f,   1.0f, 1.0f, 1.0f,
        -1.0f, -0.9f, 0.0f,   1.0f, 1.0f, 1.0f,
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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложени€ текстуры GL_REPEAT (стандартный метод наложени€)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // ”становка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
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
        // –ендеринг
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
        progres_bar_tick();
        glBindVertexArray(loader_line_progress_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        



        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }



    // glfw: завершение, освобождение всех ранее задействованных GLFW-ресурсов
    glfwTerminate();
    return;
}
