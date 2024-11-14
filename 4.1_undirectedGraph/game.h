//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#pragma once
#include<shader.h>
#include<graph.hpp>
#include<game_object.h>

#include<vector>


class Game {
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Init(GLFWwindow* window);
	void ProcessInput(GLfloat x, GLfloat y);
	void update(float dt);
	void Render();
	void changeNum() {
		numVertex = (numVertex + 1) % 4;
	}

private:
	Game(): graphData(20), gameVertex(0), gameEdge(0), numVertex(0), numEdge(0),
		isRendering(false), interactive(true), 
		NodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), EdgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")){}

	void addVertex(GLfloat x, GLfloat y);
	void addEdge(int v1, int v2);
	int targetPoint(GLfloat x, GLfloat y);

	Minw::undirectedGraph<int, int> graphData;
	std::vector<painter::Node> gameVertex;
	std::vector<painter::Edge> gameEdge;
	Shader NodeShader;
	Shader EdgeShader;
	bool isRendering;
	bool interactive;
	int lastPoint = -1;
	int numVertex;
	int numEdge;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);
