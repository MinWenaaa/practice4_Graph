//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#include"shader.h"
#include"game.h"
#include<GLFW/glfw3.h>

#include<graph.hpp>
#include<iostream>

#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200
#define PI 3.14159265358979323846

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//void upload_ourColor(Shader shaderProgram);


int main() {

	GLFWwindow* window = WindowParas::getInstance().window;
	Game::getInstance().Init(window);
	GLfloat lineWidthRange[2];
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
	std::cout << "Min line width: " << lineWidthRange[0] << ", Max line width: " << lineWidthRange[1] << std::endl;
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glLineWidth(1.0f);
		//std::cout << glGetError() << std::endl;
		Game::getInstance().Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//void upload_ourColor(Shader shader) {
//	float timeValue = glfwGetTime();
//	float yValue = sin(timeValue * 2);
//	shader.setVec3("transform", 0.0f, yValue, 0.0f);
//}