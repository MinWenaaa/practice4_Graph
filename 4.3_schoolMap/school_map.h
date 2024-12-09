//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include"shader.h"
#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200

class SchoolMap {
public:
	static SchoolMap& getInstance() {
		static SchoolMap instance;
		return instance;
	}
	SchoolMap(const SchoolMap&) = delete;
	SchoolMap& operator=(const SchoolMap&) = delete;

	void ProcessInput(GLfloat x, GLfloat y);
	void ProcessMouseScroll(float yoffset, float xpos, float ypos);
	void ProcessMouseDrag(float xpos, float ypos);
	void Render();

	void initCursorPos(float xpos, float ypos);

private:
	SchoolMap();
	void upDateRotationMatrix();

	GLuint base_map, VAO, VBO, EBO;
	int width, height, nrChannels;		// 底图影像的长宽高

	Shader nodeShader, edgeShader, backgroundShader;
	glm::mat4 model;
};
