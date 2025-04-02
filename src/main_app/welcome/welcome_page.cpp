#include "welcome_page.h"


int WIDTH = 773, HEIGHT = 628;

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }


    float box_vertices[] = {
        50.0f, 50.0f, 0.0f,      1.0f, 1.0f, 
        50.0f, 500.0f, 0.0f,     1.0f, 0.0f, 
        500.0f, 500.0f, 0.0f,    0.0f, 0.0f,
        500.0f, 50.0f, 0.0f,     0.0f, 1.0f,
        
    };

    unsigned int box_VAO, box_VBO;
    glGenVertexArrays(1, &box_VAO);
    glGenBuffers(1, &box_VBO);

    glBindVertexArray(box_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, box_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box_vertices), box_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int box_texture;

    glGenTextures(1, &box_texture);
    glBindTexture(GL_TEXTURE_2D, box_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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


    Shader plain_shader("src/main_app/shaders/plain.vs", "src/main_app/shaders/plain.fs");
    Shader texture_shader("src/main_app/shaders/texture.vs", "src/main_app/shaders/texture.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.11764705f, 0.12156862f, 0.1333333f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        texture_shader.use();
        texture_shader.setMat4("projection", projection);
        glBindVertexArray(box_VAO);
        glBindTexture(GL_TEXTURE_2D, box_texture);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return;
}

/*

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4  projection)
{
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        CharacterStruct ch = Characters_list[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glLoadIdentity();
}*/


void processInput(GLFWwindow* window)
{
    double mouse_x_pos, mouse_y_pos;
    glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        // window nav bar

    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}