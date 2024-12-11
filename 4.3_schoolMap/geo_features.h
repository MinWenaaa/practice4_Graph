#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>

#include"shader.h"

#include<string>
#include<cmath>

const float cubeSize = 0.05;
class Building {
public:
	Building(GLfloat x, GLfloat y, Shader* shader, std::string name);
	void draw();
	void changeSelected();
	float getDistance(float X, float Y) {
		return sqrt((x - X) * (x - X) + (y - Y) * (y - Y));
	}

	std::string name;
private:
	Shader* shader;
	GLuint VBO, VAO, EBO, VBO_color;
	GLfloat x, y;
	bool isSelected;
};