#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>

#include"shader.h"

#include<string>

const float cubeSize = 0.05;
class Building {
public:
	Building(GLfloat x, GLfloat y, Shader* shader, std::string name);
	void draw();

	std::string name;
private:
	Shader* shader;
	GLuint VBO, VAO, EBO;
	GLfloat x, y;
	bool isSelected;
};