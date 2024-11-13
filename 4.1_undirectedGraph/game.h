//
//-------------------- for the 4.1_undirectedGraph ----------------------
//

#pragma once
#include<shader.h>
#include<data_structure/graph.hpp>
#include<vector>
#include<game_object.h>


class Game {
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	
	~Game();

	void Init(GLFWwindow* window);
	void ProcessInput(GLfloat x, GLfloat y);
	void update(float dt);
	void Render();

private:
	Game(): graphData(20), gameVertex(0), gameEdge(0), isRendering(false), interactive(true) {}

	Minw::undirectedGraph<int, int> graphData;
	std::vector<painter::Node> gameVertex;
	std::vector<painter::Edge> gameEdge;
	bool isRendering;
	bool interactive;
};

void mouseCallback(GLFWwindow* window, int button, int action, int mods);
