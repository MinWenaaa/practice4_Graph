//
//-------------------- for the 4.3_schoolMap ----------------------
//

#include"shader.h"
#include<GLFW/glfw3.h>

#include<graph.hpp>
#include<iostream>

#include"school_map.h"

#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool isDragging;

int main() {

	GLFWwindow* window = WindowParas::getInstance().window;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SchoolMap::getInstance().Render(); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	WindowParas& windowPara = WindowParas::getInstance();
	GLdouble xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	SchoolMap::getInstance().ProcessMouseScroll(yoffset, windowPara.screen2normalX(xpos), windowPara.screen2normalY(ypos));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		SchoolMap::getInstance().initCursorPos(xpos, ypos);
		isDragging = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) 
		isDragging = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (isDragging) {
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		SchoolMap::getInstance().ProcessMouseDrag(xpos, ypos);
	}
}
