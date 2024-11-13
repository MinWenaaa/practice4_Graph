//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#include "game.h"
#include<iostream>

Game::~Game() {

}
//---------------------------------------------------------------------------------
void Game::Init(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, mouseCallback);
}
//---------------------------------------------------------------------------------
void Game::update(float dt) {

}
//---------------------------------------------------------------------------------
void Game::ProcessInput(GLfloat x, GLfloat y) {
	std::cout << "click x: " << x << "; click y: " << y << std::endl;
}
//---------------------------------------------------------------------------------
void Game::Render() {

}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)	{
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Game::getInstance().ProcessInput(windowPara.screen2normalX(xpos), windowPara.screen2normalY(ypos));
	}
}