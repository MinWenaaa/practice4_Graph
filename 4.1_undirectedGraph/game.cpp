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
	if (isRendering) return;	// 正在深度/广度遍历，禁止操作

	int target = targetPoint(x, y);
	if (target == -1) {				// 插入节点
		addVertex(x, y);
		lastPoint = -1;

	} else if (lastPoint == -1) {	// 选择节点
		lastPoint = target;

	} else if (lastPoint == target) {// 随机深度/广度优先
		graphData.DFS(target);
		isRendering = true;
		for (int i = 0; i < numVertex; i++) 
		{
			this->gameVertex[i].depth = graphData.getDepthN(i);
			this->gameVertex[i].setCoverColor(nextColor);
		}
		for (int i = 0; i < numEdge; i++)
		{
			this->gameEdge[i].depth = graphData.getDepthE(this->gameEdge[i].v1, this->gameEdge[i].v2);
			if (gameVertex[gameEdge[i].v1].depth > gameVertex[gameEdge[i].v2].depth)gameEdge[i].start = gameEdge[i].v2;
			else gameEdge[i].start = gameEdge[i].v1;
			this->gameEdge[i].setCoverColor(nextColor);
		}
		
		current_depth = 0;
		lastPoint = -1;

	} else {						// 插入边
		addEdge(lastPoint, target);
		lastPoint = -1;
	}
}
int Game::targetPoint(GLfloat x, GLfloat y) {
	bool flag = false;
	for (int i = 0; i < numVertex; i++) {
		if (abs(x - gameVertex[i].x) < 0.03 && abs(y - gameVertex[i].y) < 0.03)
			return i;
	}
	return -1;
}
//---------------------------------------------------------------------------------
void Game::addVertex(GLfloat x, GLfloat y) {
	this->graphData.insertVertex(numVertex);
	this->numVertex++;
	std::cout << glGetError() << std::endl;
	painter::Node node(x, y, color, &NodeShader);
	this->gameVertex.push_back(node);
	std::cout << "Insert Point: " << numVertex << std::endl;
}

void Game::addEdge(int v1, int v2) {
	this->graphData.insertEdge(v1, v2, 0);
	this->numEdge++;
	GLfloat points[] = { gameVertex[v1].x, gameVertex[v1].y, gameVertex[v2].x, gameVertex[v2].y };
	painter::Edge edge(points, color, v1, v2, v1, &EdgeShader);
	this->gameEdge.push_back(edge);
	std::cout << "Insert Edge: " << numEdge << " between" << v1 << " and " << v2 << std::endl;
}
//---------------------------------------------------------------------------------
void Game::Render() {
	//std::cout << "Game Render Begin: " << glGetError() << std::endl;
	for (int i = 0; i < numEdge; i++) 
		this->gameEdge[i].draw_baseLayer();
	for (int i = 0; i < numVertex; i++) 
		this->gameVertex[i].draw_baseLayer();
		//std::cout << glGetError() << std::endl;

	if (isRendering) {
		if (pocess > 1) {
			pocess = 0;
			current_depth += 1;
		}
		for (int i = 0; i < numEdge; i++) 
		{
			if (this->gameEdge[i].depth != current_depth) continue;
			this->gameEdge[i].draw_coverLayer(pocess);
			return;
		}
		for (int i = 0; i < numVertex; i++) {
			if (this->gameVertex[i].depth != current_depth) continue;
			this->gameVertex[i].draw_coverLayer(pocess);
			return;
		}
		color = nextColor;
		nextColor = (nextColor + 1) % 6;
		isRendering = false;
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