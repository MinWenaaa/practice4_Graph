//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#include "game.h"
#include<iostream>

//---------------------------------------------------------------------------------
void Game::Init(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseCallback);
	addVertex(0.1f, 0.1f);
	addVertex(0.3f, 0.3f);
	addVertex(0.5f, 0.5f);
}
//---------------------------------------------------------------------------------
void Game::update(float dt) {

}
//---------------------------------------------------------------------------------
void Game::ProcessInput(GLfloat x, GLfloat y) {
	std::cout << "click x: " << x << "; click y: " << y << std::endl;
	if (lastPoint == -1) {
		addVertex(x, y);
	}
}
//---------------------------------------------------------------------------------
void Game::Render() {
	for (int i = 0; i < numVertex; i++) {
		this->gameVertex[i].draw();
		//std::cout << glGetError() << std::endl;
	}
}

void Game::addVertex(GLfloat x, GLfloat y) {
	this->graphData.insertVertex(numVertex);
	this->numVertex++;
	painter::Node node(x, y, &NodeShader);
	this->gameVertex.push_back(std::move(node));
	std::cout << numVertex << std::endl;
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)	{
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Game::getInstance().ProcessInput(windowPara.screen2normalX(xpos), windowPara.screen2normalY(ypos));
	}
}