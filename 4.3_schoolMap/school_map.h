//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include"shader.h"
#include"geo_features.h"

#include<cmath>
#include<string>
#include<vector>

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

	void loadData(std::string fileName);

	GLuint base_map, VAO, VBO, EBO;
	int width, height, nrChannels;		// 底图影像的长宽高

	Shader nodeShader, edgeShader, backgroundShader, cubeShader;
	glm::mat4 model, projection;

	std::vector<Building> buildings;
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
