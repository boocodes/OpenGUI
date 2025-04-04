#include "projects_subpage.h"

Projects_subpage::Projects_subpage(int SCR_WIDTH, int SCR_HEIGHT)
{
	this->SCR_HEIGHT = SCR_HEIGHT;
	this->SCR_WIDTH = SCR_WIDTH;
	Font font("assets/Roboto-Medium.ttf", this->SCR_WIDTH, this->SCR_HEIGHT);
	Font font_regular("assets/Roboto-Regular.ttf", this->SCR_WIDTH, this->SCR_HEIGHT);
	font.init();
	font_regular.init();
	this->font_list.push_back(font);
	this->font_list.push_back(font_regular);
	

	float new_project_box_vertices[] = {
		352.0f, 295.0f, 0.0f,
		409.0f, 295.0f, 0.0f,
		409.0f, 240.0f, 0.0f,
		352.0f, 240.0f, 0.0f,
	};

	float open_exist_project_box_vertices[] = {
		472.0f, 295.0f, 0.0f,
		529.0f, 295.0f, 0.0f,
		529.0f, 240.0f, 0.0f,
		472.0f, 240.0f, 0.0f,
	};

	float clone_repos_box_vertices[] = {
		592.0f, 295.0f, 0.0f,
		649.0f, 295.0f, 0.0f,
		649.0f, 240.0f, 0.0f,
		592.0f, 240.0f, 0.0f,
	};

	unsigned int new_project_select_box_VAO, new_project_select_box_VBO;
	glGenVertexArrays(1, &new_project_select_box_VAO);
	glGenBuffers(1, &new_project_select_box_VBO);
	
	glBindVertexArray(new_project_select_box_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, new_project_select_box_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_project_box_vertices), new_project_box_vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	this->VAO_list.push_back(new_project_select_box_VAO);

	unsigned int open_exist_project_box_VAO, open_exist_project_box_VBO;
	glGenVertexArrays(1, &open_exist_project_box_VAO);
	glGenBuffers(1, &open_exist_project_box_VBO);

	glBindVertexArray(open_exist_project_box_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, open_exist_project_box_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(open_exist_project_box_vertices), open_exist_project_box_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	this->VAO_list.push_back(open_exist_project_box_VAO);


	unsigned int clone_repos_box_VAO, clone_repos_box_VBO;
	glGenVertexArrays(1, &clone_repos_box_VAO);
	glGenBuffers(1, &clone_repos_box_VBO);
	glBindVertexArray(clone_repos_box_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, clone_repos_box_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(clone_repos_box_vertices), clone_repos_box_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	this->VAO_list.push_back(clone_repos_box_VAO);

	Shader plain("src/main_app/shaders/plain.vs", "src/main_app/shaders/plain.fs");
	this->shader_list.push_back(plain);
	glm::mat4 projection = glm::ortho(0.0f, (float)this->SCR_WIDTH, 0.0f, (float)this->SCR_HEIGHT, -1.0f, 1.0f);
	this->projection_list.push_back(projection);
}

void Projects_subpage::show_project_subpage()
{
	this->font_list.at(0).set_scale(0.6f);
	this->font_list.at(0).set_color(glm::vec3(1.0f, 1.0f, 1.0f));
		this->font_list.at(0).RenderText("Welcome OpenGUI", 375.0f, 461.0f);
	this->font_list.at(1).set_color(glm::vec3(0.34901960784313724, 0.3607843137254902, 0.3843137254901961));
	this->font_list.at(1).set_scale(0.4f);
		this->font_list.at(1).RenderText("Create a new project to start", 375.0f, 401.0f);
		this->font_list.at(1).RenderText("Open existing project from disk or version controll", 290.0f, 360.0f);


	this->shader_list.at(0).use();
	this->shader_list.at(0).setMat4("projection", this->projection_list.at(0));
	this->shader_list.at(0).setVec3("color", glm::vec3(0.16862745098039217, 0.17647058823529413, 0.18823529411764706));
	glBindVertexArray(this->VAO_list.at(0));
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	

	glBindVertexArray(this->VAO_list.at(1));
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
	glBindVertexArray(this->VAO_list.at(2));
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	this->font_list.at(1).set_color(glm::vec3(1.0f, 1.0f, 1.0f));
	this->font_list.at(1).RenderText("New project", 344.0f, 156.0f);
	this->font_list.at(1).RenderText("Open", 489.0f, 156.0f);
	this->font_list.at(1).RenderText("Clone", 578.0f, 156.0f);


}
