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

int main() {

	GLFWwindow* window = WindowParas::getInstance().window;
	SchoolMap::getInstance().Init(window);

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