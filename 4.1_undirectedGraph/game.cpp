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
	int target = targetPoint(x, y);

	if (target == -1) {				// 插入节点
		addVertex(x, y);

	} else if (lastPoint == -1) {	// 选择节点
		lastPoint = target;

	} else if (lastPoint == target) {// 随机深度/广度优先


	} else {						// 插入边
		addEdge(lastPoint, target);
	}
}
int Game::targetPoint(GLfloat x, GLfloat y) {
	bool flag = false;
	for (int i = 0; i < numVertex; i++) {
		if (abs(x - gameVertex[i].vertices[0]) < gameVertex[i].radius && abs(y - gameVertex[i].vertices[1]) < gameVertex[i].radius)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------------
void Game::addVertex(GLfloat x, GLfloat y) {
	this->graphData.insertVertex(numVertex);
	this->numVertex++;
	painter::Node node(x, y, &NodeShader);
	this->gameVertex.push_back(std::move(node));
	std::cout << numVertex << std::endl;
}

void Game::addEdge(int v1, int v2) {
	this->graphData.insertEdge(v1, v2, 0);
	this->numEdge++;
	GLfloat* points = new GLfloat[4];
	points[0] = gameVertex[v1].vertices[0];
	points[1] = gameVertex[v1].vertices[1];
	points[2] = gameVertex[v2].vertices[0];
	points[3] = gameVertex[v2].vertices[1];
	painter::Edge edge(points, &EdgeShader);
	this->gameEdge.push_back(std::move(edge));
	delete[] points;
	std::cout << numEdge << std::endl;
}
//---------------------------------------------------------------------------------
void Game::Render() {
	for (int i = 0; i < numVertex; i++) {
		this->gameVertex[i].draw();
		//std::cout << glGetError() << std::endl;
	}
	for (int i = 0; i < numEdge; i++) {
		this->gameEdge[i].draw();
	}
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)	{
		WindowParas& windowPara = WindowParas::getInstance();
		GLdouble xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Game::getInstance().ProcessInput(windowPara.screen2normalX(xpos), windowPara.screen2normalY(ypos));
	}
}