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

	Shader NodeShader;

	Game(): 
		graphData(20), gameVertex(0), gameEdge(0),
		isRendering(false), interactive(true), NodeShader(Shader("../mylib/node.vs", "../mylib/node.fs")) {
		numVertex = 0;
	}

	void addVertex(GLfloat x, GLfloat y);

	Minw::undirectedGraph<int, int> graphData;
	std::vector<painter::Node> gameVertex;
	std::vector<painter::Edge> gameEdge;
	bool isRendering;
	bool interactive;
	int lastPoint = -1;
	int numVertex;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);
