//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include"shader.h"

class SchoolMap {
public:
	static SchoolMap& getInstance() {
		static SchoolMap instance;
		return instance;
	}
	SchoolMap(const SchoolMap&) = delete;
	SchoolMap& operator=(const SchoolMap&) = delete;

	void Init(GLFWwindow* window);
	void ProcessInput(GLfloat x, GLfloat y);
	void Render();

private:
	SchoolMap();

	GLuint base_map, VAO, VBO;
	int width, height, nrChannels;		// 底图影像的长宽高

	Shader nodeShader, edgeShader, backgroundShader;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);