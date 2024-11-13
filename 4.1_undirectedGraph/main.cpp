#include"shader.h"
#include"game.h"
#include<GLFW/glfw3.h>

#include<data_structure/graph.hpp>
#include<iostream>


#define SCR_WIDTH 1600
#define SCR_HEIGHT 1200

void vertex_buffer_object(unsigned int& VBO, unsigned int& VAO);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void upload_ourColor(Shader shaderProgram);



int main() {

	GLFWwindow* window = WindowParas::getInstance().window;

	Shader ourShader("shader.vs", "shader.fs");

	unsigned int VBO, VAO;
	vertex_buffer_object(VBO, VAO);


	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		upload_ourColor(ourShader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
	
//	char cmd;
//	int v1, v2, v3;
//	while (true) {
//		std::cin >> cmd;
//		switch (cmd) {
//		case 'v':
//			std::cin >> v1;
//			graph.insertVertex(v1);
//			break;
//		case 'e':
//			std::cin >> v1 >> v2 >> v3;
//			graph.insertEdge(v1, v2, v3);
//			break;
//		case 'r':
//			std::cin >> v1;
//			graph.removeVertex(v1);
//			break;
//		case 'R':
//			std::cin >> v1 >> v2;
//			graph.removeEdge(v1, v2);
//			break;
//		case 'x':
//			return 0;
//		}
//	}
//	return 0;
}

void vertex_buffer_object(unsigned int& VBO, unsigned int& VAO) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void upload_ourColor(Shader shader) {
	float timeValue = glfwGetTime();
	float yValue = sin(timeValue * 2);
	shader.setVec3("transform", 0.0f, yValue, 0.0f);
}