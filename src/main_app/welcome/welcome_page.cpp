#include "welcome_page.h"









bool minimize_icon_hover = false,
close_icon_hover = false;
int active_menu_item = 1;

int WIDTH = 773, HEIGHT = 628;

float top_bar_vertices[] = {
    0.0f, static_cast<float>(HEIGHT), 0.0f,
    static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f,
    static_cast<float>(WIDTH), static_cast<float>(HEIGHT) - 35.0f, 0.0f,
    0.0f, static_cast<float>(HEIGHT) - 35.0f, 0.0f,
};
float left_bar_vertices[] = {
    0.0f, static_cast<float>(HEIGHT) - 37.0f, 0.0f,
    220.0f, static_cast<float>(HEIGHT) - 37.0f, 0.0f,
    220.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
};
float minimize_icon_vertices[] = {
    676.0f, 619.0f, 0.0f,   1.0f, 1.0f,
    696.0f, 619.0f, 0.0f,   1.0f, 0.0f,
    696.0f, 605.0f, 0.0f,   0.0f, 0.0f,
    676.0f, 605.0f, 0.0f,   0.0f, 1.0f,
};
float under_minimize_icon_box_vertices[] = {
    668.0f, static_cast<float>(HEIGHT), 0.0f,
    703.0f, static_cast<float>(HEIGHT), 0.0f,
    703.0f, static_cast<float>(HEIGHT) - 35.0f, 0.0f,
    668.0f, static_cast<float>(HEIGHT) - 35.0f, 0.0f,
};

float close_icon_vertices[] = {
    733.0f, 621.0f, 0.0f,   1.0f, 1.0f,
    752.0f, 621.0f, 0.0f,   1.0f, 0.0f,
    752.0f, 603.0f, 0.0f,   0.0f, 0.0f,
    733.0f, 603.0f, 0.0f,   0.0f, 1.0f,
};
float under_close_icon_box_vertices[] = {
    725.0f, static_cast<float>(HEIGHT), 0.0f,
    760.0f, static_cast<float>(HEIGHT), 0.0f,
    760.0f, static_cast<float>(HEIGHT) - 35.0f, 0.0f,
    725.0f, static_cast<float>(HEIGHT) - 35.0f, 0.0f,
};

float under_active_menu_item_vertices[] = {
    10.0f, 540.0f, 0.0f,
    200.0f, 540.0f, 0.0f,
    200.0f, 495.0f, 0.0f,
    10.0f, 495.0f, 0.0f,
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // FONT 
    
    Font font("assets/Roboto-Medium.ttf", WIDTH, HEIGHT);

    font.init();
    

    
    // FONT

    unsigned int top_bar_VAO, top_bar_VBO;
    glGenVertexArrays(1, &top_bar_VAO);
    glGenBuffers(1, &top_bar_VBO);

    glBindVertexArray(top_bar_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, top_bar_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(top_bar_vertices), top_bar_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int left_bar_VAO, left_bar_VBO;
    glGenVertexArrays(1, &left_bar_VAO);
    glGenBuffers(1, &left_bar_VBO);

    glBindVertexArray(left_bar_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, left_bar_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(left_bar_vertices), left_bar_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int minimize_icon_VAO, minimize_icon_VBO;
    unsigned int minimize_icon_texture = made_texture_png("assets/minimize.png");

    glGenVertexArrays(1, &minimize_icon_VAO);
    glGenBuffers(1, &minimize_icon_VBO);

    glBindVertexArray(minimize_icon_VAO);   
    glBindBuffer(GL_ARRAY_BUFFER, minimize_icon_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(minimize_icon_vertices), minimize_icon_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int close_icon_VAO, close_icon_VBO;
    unsigned int close_icon_texture = made_texture_png("assets/close.png");
    
    glGenVertexArrays(1, &close_icon_VAO);
    glGenBuffers(1, &close_icon_VBO);

    glBindVertexArray(close_icon_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, close_icon_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(close_icon_vertices), close_icon_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    
    unsigned int under_minimize_box_VAO, under_minimize_box_VBO;
    glGenVertexArrays(1, &under_minimize_box_VAO);
    glGenBuffers(1, &under_minimize_box_VBO);

    glBindVertexArray(under_minimize_box_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, under_minimize_box_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(under_minimize_icon_box_vertices), under_minimize_icon_box_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int under_close_box_VAO, under_close_box_VBO;
    glGenVertexArrays(1, &under_close_box_VAO);
    glGenBuffers(1, &under_close_box_VBO);

    glBindVertexArray(under_close_box_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, under_close_box_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(under_close_icon_box_vertices), under_close_icon_box_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int under_active_menu_item_VAO, under_active_menu_item_VBO;
    glGenVertexArrays(1, &under_active_menu_item_VAO);
    glGenBuffers(1, &under_active_menu_item_VBO);

    glBindVertexArray(under_active_menu_item_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, under_active_menu_item_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(under_active_menu_item_vertices), under_active_menu_item_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);



    
    Shader plain("src/main_app/shaders/plain.vs", "src/main_app/shaders/plain.fs");

    glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);


    Shader texture("src/main_app/shaders/texture.vs", "src/main_app/shaders/texture.fs");


    Shader static_variable("src/main_app/shaders/static_variable.vs", "src/main_app/shaders/static_variable.fs");
    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.11764705f, 0.12156862f, 0.1333333f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // top and left static bar
        plain.use();
        plain.setMat4("projection", projection);
        plain.setVec3("color", glm::vec3(0.16862745098039217, 0.17647058823529413, 0.18823529411764706));

        glBindVertexArray(top_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(left_bar_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // ------

        // hover minimize and close boxes
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        plain.use();
        plain.setMat4("projection", projection);
        
        if (minimize_icon_hover)
        {
            plain.setVec3("color", glm::vec3(0.09411764705882353, 0.3764705882352941, 0.796078431372549));
            glBindVertexArray(under_minimize_box_VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
        if (close_icon_hover)
        {
            plain.setVec3("color", glm::vec3(0.09411764705882353, 0.3764705882352941, 0.796078431372549));
            glBindVertexArray(under_close_box_VAO);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
        // -------
       

        // minimize and close buttons
        texture.use();
        texture.setMat4("projection", projection);

        glBindTexture(GL_TEXTURE_2D, minimize_icon_texture);
        glBindVertexArray(minimize_icon_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindTexture(GL_TEXTURE_2D, close_icon_texture);
        glBindVertexArray(close_icon_VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        // ------
        
        // active menu items box
        static_variable.use();
        glBindVertexArray(under_active_menu_item_VAO);
        static_variable.setFloat("translate_x", 1.0f);
        
        static_variable.setMat4("projection", projection);
        static_variable.setVec3("color", glm::vec3(0.09411764705882353, 0.3764705882352941, 0.796078431372549));
        if (active_menu_item == 1)
        {
            static_variable.setFloat("translate_y", 0.0f);
        }
        else if (active_menu_item == 2)
        {
            static_variable.setFloat("translate_y", 60.0f);
        }
        else if (active_menu_item == 3)
        {
            static_variable.setFloat("translate_y", 120.0f);
        }
        else if (active_menu_item == 4)
        {
            static_variable.setFloat("translate_y", 180.0f);
        }
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    
        font.set_color(glm::vec3(0.34509803921568627, 0.34901960784313724, 0.3568627450980392));
        font.set_scale(0.35);
        font.RenderText("OpenGUI v0.1", 18.0f, 605.0f);



        font.set_color(glm::vec3(1.0f, 1.0f, 1.0f));
        font.set_scale(0.4);
        font.RenderText("Projects", 25.0f, 510.0f);
        font.RenderText("Environment", 25.0f, 450.0f);
        font.RenderText("Addons", 25.0f, 390.0f);
        font.RenderText("Documentation", 25.0f, 330.0f);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return;
}




void processInput(GLFWwindow* window)
{
    double mouse_x_pos, mouse_y_pos;
    glfwGetCursorPos(window, &mouse_x_pos, &mouse_y_pos);

    // top nav bar elem hover
    // minimize 
    if (
        (mouse_x_pos >= under_minimize_icon_box_vertices[0] && mouse_x_pos <= under_minimize_icon_box_vertices[3] && mouse_x_pos <= under_minimize_icon_box_vertices[6] && mouse_x_pos >= under_minimize_icon_box_vertices[9])
        &&
        (HEIGHT - mouse_y_pos <= under_minimize_icon_box_vertices[1] && HEIGHT - mouse_y_pos <= under_minimize_icon_box_vertices[4] && HEIGHT - mouse_y_pos >= under_minimize_icon_box_vertices[7] && HEIGHT - mouse_y_pos >= under_minimize_icon_box_vertices[11])
        )
    {
        minimize_icon_hover = true;
    }
    else
    {
        minimize_icon_hover = false;
    }

    // close

    if (
        (mouse_x_pos >= under_close_icon_box_vertices[0] && mouse_x_pos <= under_close_icon_box_vertices[3] && mouse_x_pos <= under_close_icon_box_vertices[6] && mouse_x_pos >= under_close_icon_box_vertices[9])
        &&
        (HEIGHT - mouse_y_pos <= under_close_icon_box_vertices[1] && HEIGHT - mouse_y_pos <= under_close_icon_box_vertices[4] && HEIGHT - mouse_y_pos >= under_close_icon_box_vertices[7] && HEIGHT - mouse_y_pos >= under_close_icon_box_vertices[11])
        )
    {
        close_icon_hover = true;
    }
    else
    {
        close_icon_hover = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        // close button
        if (
            (mouse_x_pos >= under_close_icon_box_vertices[0] && mouse_x_pos <= under_close_icon_box_vertices[3] && mouse_x_pos <= under_close_icon_box_vertices[6] && mouse_x_pos >= under_close_icon_box_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_close_icon_box_vertices[1] && HEIGHT - mouse_y_pos <= under_close_icon_box_vertices[4] && HEIGHT - mouse_y_pos >= under_close_icon_box_vertices[7] && HEIGHT - mouse_y_pos >= under_close_icon_box_vertices[11])
            )
        {
            glfwTerminate();
            exit(0);
        }
        // minimize button
        if (
            (mouse_x_pos >= under_minimize_icon_box_vertices[0] && mouse_x_pos <= under_minimize_icon_box_vertices[3] && mouse_x_pos <= under_minimize_icon_box_vertices[6] && mouse_x_pos >= under_minimize_icon_box_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_minimize_icon_box_vertices[1] && HEIGHT - mouse_y_pos <= under_minimize_icon_box_vertices[4] && HEIGHT - mouse_y_pos >= under_minimize_icon_box_vertices[7] && HEIGHT - mouse_y_pos >= under_minimize_icon_box_vertices[11])
            )
        {
            glfwIconifyWindow(window);
        }

        // menu items
        if (
            (mouse_x_pos >= under_active_menu_item_vertices[0] && mouse_x_pos <= under_active_menu_item_vertices[3] && mouse_x_pos <= under_active_menu_item_vertices[6] && mouse_x_pos >= under_active_menu_item_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[1] && HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[4] && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[7] && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[11])
            )
        {
            active_menu_item = 1;
        }
        if (
            (mouse_x_pos >= under_active_menu_item_vertices[0] && mouse_x_pos <= under_active_menu_item_vertices[3] && mouse_x_pos <= under_active_menu_item_vertices[6] && mouse_x_pos >= under_active_menu_item_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[1] - 60 && HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[4] - 60 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[7] - 60 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[11] - 60)
            )
        {
            active_menu_item = 2;
        }
        if (
            (mouse_x_pos >= under_active_menu_item_vertices[0] && mouse_x_pos <= under_active_menu_item_vertices[3] && mouse_x_pos <= under_active_menu_item_vertices[6] && mouse_x_pos >= under_active_menu_item_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[1] - 120 && HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[4] - 120 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[7] - 120 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[11] - 120)
            )
        {
            active_menu_item = 3;
        }
        if (
            (mouse_x_pos >= under_active_menu_item_vertices[0] && mouse_x_pos <= under_active_menu_item_vertices[3] && mouse_x_pos <= under_active_menu_item_vertices[6] && mouse_x_pos >= under_active_menu_item_vertices[9])
            &&
            (HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[1] - 180 && HEIGHT - mouse_y_pos <= under_active_menu_item_vertices[4] - 180 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[7] - 180 && HEIGHT - mouse_y_pos >= under_active_menu_item_vertices[11] - 180)
            )
        {
            active_menu_item = 4;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

