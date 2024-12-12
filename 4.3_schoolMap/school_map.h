//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include"shader.h"
#include"geo_features.h"
#include"graph.hpp"
#include"game_object.h"

#include<cmath>
#include<string>
#include<vector>
#include<iostream>
#include<sstream>

namespace school_map {
	struct Node {
		float x, y;
		int label;
		Node() : x(0), y(0), label(0) {}
		Node(const std::string& str) {
			std::istringstream iss(str);
			iss >> label >> x >> y;
		}
	};

	std::ostream& operator<<(std::ostream& os, const Node& node);
}

class SchoolMap {
public:
	static SchoolMap& getInstance() {
		static SchoolMap instance;
		return instance;
	}
	SchoolMap(const SchoolMap&) = delete;
	SchoolMap& operator=(const SchoolMap&) = delete;

	void ProcessInput(GLfloat x, GLfloat y);
	void Render();
	void adaptation(float a);
	std::string getCurrentName() {
		if (currentBuilding == -1) return "no point selected";
		return buildings[currentBuilding].name;
	}
	void setStart() { 
		if(start>-1&&start<buildings.size()) buildings[start].changeSelected(false);
		start = currentBuilding; }
	void setEnd() { 
		if (target>-1 && target < buildings.size())buildings[target].changeSelected(false);
		target = currentBuilding; }
	void navigation();

	glm::mat4 projection;

private:
	SchoolMap();

	void addNode(school_map::Node node);
	void addEdge(int v1, int v2);

	void loadBuildingData(std::string fileName);
	void loadGraphData(std::string fileName);

	GLuint base_map, VAO, VBO, EBO;
	int width, height, nrChannels;		// 底图影像的长宽高

	Shader nodeShader, edgeShader, backgroundShader, cubeShader;

	std::vector<Building> buildings;
	std::vector<school_map::Node> nodes;
	std::vector<painter::Edge> roads;
	int numNode, numEdge;

	Minw::undirectedGraph<int, float> schoolRoad;

	int currentBuilding, start, target;
	float currentDistance;
};

class MyGUI {
public:
	static MyGUI& getInstance() {
		static MyGUI instance;
		return instance;
	}
	MyGUI(const MyGUI&) = delete;
	MyGUI& operator=(const MyGUI&) = delete;

	void init(GLFWwindow* window);
	void Render(int w, int h);

private:
	MyGUI() {}

	bool isShowDrag = false;
	std::string text = "";
	float fValue = 0.5f;

};
