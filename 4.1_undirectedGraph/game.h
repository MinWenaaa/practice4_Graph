#pragma once
#include<data_structure/graph.hpp>
#include<vector>
#include<game_object.h>

enum GameState {

};

class Game {
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	}
	
	~Game();

	void Init();
	void ProcessInput(float dt);
	void update(float dt);
	void Render();

private:
	Game(): graphData(20), gameVertex(0), gameEdge(0) {}

	GameState State;
	Minw::undirectedGraph<int, int> graphData;
	std::vector<painter::Node> gameVertex;
	std::vector<painter::Edge> gameEdge;
	bool isRendering;
	bool interactive;
};
