#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>

#include"shader.h"

#include<string>
#include<cmath>

const float cubeSize = 0.05;
class Building {
public:
	Building(GLfloat x, GLfloat y, int node, Shader* shader, std::string name);
	void draw();
	void changeSelected(bool b);
	float getDistance(float X, float Y) {
		return sqrt((x - X) * (x - X) + (y - Y) * (y - Y));
	}

	std::string name;
	int node;
private:
	Shader* shader;
	GLuint VBO, VAO, EBO, VBO_color;
	GLfloat x, y;
	bool isSelected;
};