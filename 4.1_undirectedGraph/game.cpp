//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#include "game.h"
#include<iostream>

//---------------------------------------------------------------------------------
void Game::Init(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseCallback);
}
//---------------------------------------------------------------------------------
void Game::update(float dt) {

}
//---------------------------------------------------------------------------------
void Game::ProcessInput(GLfloat x, GLfloat y) {
	std::cout << "click x: " << x << ", y : " << y << "; glGetError():" << glGetError() << std::endl;
	int target = targetPoint(x, y);

	if (target == -1) {				// 插入节点
		addVertex(x, y);
		lastPoint = -1;

	} else if (lastPoint == -1) {	// 选择节点
		lastPoint = target;

	} else if (lastPoint == target) {// 随机深度/广度优先


	} else {						// 插入边
		addEdge(lastPoint, target);
		lastPoint = -1;
	}
}
int Game::targetPoint(GLfloat x, GLfloat y) {
	bool flag = false;
	for (int i = 0; i < numVertex; i++) {
		if (abs(x - gameVertex[i].x) < gameVertex[i].pocess && abs(y - gameVertex[i].y) < gameVertex[i].pocess)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------------
void Game::addVertex(GLfloat x, GLfloat y) {
	this->graphData.insertVertex(numVertex);
	this->numVertex++;
	std::cout << glGetError() << std::endl;
	painter::Node node(x, y, 1, &NodeShader);
	this->gameVertex.push_back(std::move(node));
	std::cout << "Point: " << numVertex << std::endl;
}

void Game::addEdge(int v1, int v2) {
	this->graphData.insertEdge(v1, v2, 0);
	this->numEdge++;
	GLfloat points[] = { gameVertex[v1].x, gameVertex[v1].y, gameVertex[v2].x, gameVertex[v2].y };
	painter::Edge edge(points, 2, v1, v2, v1, &EdgeShader);
	this->gameEdge.push_back(std::move(edge));
	std::cout << numEdge << std::endl;
}
//---------------------------------------------------------------------------------
void Game::Render() {
	//std::cout << "Game Render Begin: " << glGetError() << std::endl;
	for (int i = 0; i < numVertex; i++) {
		this->gameVertex[i].draw();
		//std::cout << glGetError() << std::endl;
	}
	for (int i = 0; i < numEdge; i++) {
		this->gameEdge[i].draw();
	}
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)	{		//单击事件处理
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Game::getInstance().ProcessInput(windowPara.screen2normalX(xpos), windowPara.screen2normalY(ypos));
	}
}