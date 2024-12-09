//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include"shader.h"

#include<cmath>

class SchoolMap {
public:
	static SchoolMap& getInstance() {
		static SchoolMap instance;
		return instance;
	}
	SchoolMap(const SchoolMap&) = delete;
	SchoolMap& operator=(const SchoolMap&) = delete;

	void ProcessInput(GLfloat x, GLfloat y);
	void Render();
	void adaptation(float a);

private:
	SchoolMap();

	GLuint base_map, VAO, VBO, EBO;
	int width, height, nrChannels;		// ��ͼӰ��ĳ�����

	Shader nodeShader, edgeShader, backgroundShader;
	glm::mat4 model, projection;

};

class MyGUI {
public:
	static MyGUI& getInstance() {
		static MyGUI instance;
		return instance;
	}
	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;

	void init(GLFWwindow* window);
	void Render(int w, int h);

private:
	MyGUI() {}

	bool isShowDrag = false;
	std::string text = "";
	float fValue = 0.5f;

};
