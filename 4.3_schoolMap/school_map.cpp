#include<glad/glad.h>
#include<stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"school_map.h"

#include <array>
#include<cmath>
#include <iostream>
#include <fstream>
#include <sstream>

namespace school_map {
	std::ostream& operator<<(std::ostream& os, const Node& node) {
		os << node.label << " " << node.x << " " << node.y << std::endl;
		return os;
	}
}

SchoolMap::SchoolMap() : width(0), height(0), nrChannels(0), schoolRoad(100), numNode(0), numEdge(0), currentBuilding(-1), start(-1), target(-1),
	nodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), edgeShader(Shader("../mylib/road.vs", "../mylib/cube.fs")),
	backgroundShader(Shader("../mylib/background.vs", "../mylib/background.fs")), cubeShader(Shader("../mylib/cube.vs", "../mylib/cube.fs")) {

	glGenTextures(1, &base_map);
	glBindTexture(GL_TEXTURE_2D, base_map);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("../paint.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	float vertices[] = {
			1.0f, 8.f/9.f, 0.f,     1.0f, 1.0f,  
			1.0f, -8.f / 9.f, 0.f,    1.0f, 0.0f,
			-1.0f, -8.f / 9.f, 0.f,    0.0f, 0.0f,
			-1.0f, 8.f / 9.f, 0.f,    0.0f, 1.0f   };
	unsigned int indices[] = {
			0, 1, 3, 
			1, 2, 3 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	projection = glm::mat4(1.0f);
	projection = glm::perspective(FOV, WindowParas::getInstance().defaultAlpha, 0.1f, 100.0f);
	backgroundShader.setMat4("projection", projection);
	cubeShader.setMat4("projection", projection);
	edgeShader.setMat4("projection", projection);
	backgroundShader.use();
	glUniform1i(glGetUniformLocation(backgroundShader.ID, "ourTexture"), 0);

	loadBuildingData("data.txt");
	loadGraphData("roadData.txt");
}

void SchoolMap::ProcessInput(GLfloat x, GLfloat y) {
	std::cout << x << " " << y << std::endl;
	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i].getDistance(x, y) < cubeSize) {
			currentBuilding = i;
			break;
		}
	}
	for (int i = 0; i < buildings.size(); i++) {
		if (i == currentBuilding || i == start || i == target) buildings[i].changeSelected(true);
		else buildings[i].changeSelected(false);
	}
	//for (int i = 0; i < roads.size(); i++) {
	//	if (abs(x - nodes[i].x) < 0.02 && abs(y - nodes[i].y) < 0.02)
	//		std::cout << i << std::endl;
	//}
}

void SchoolMap::Render() {
	backgroundShader.setMat4("view", Camera::getInstance().getView());
	cubeShader.setMat4("view", Camera::getInstance().getView());
	edgeShader.setMat4("view", Camera::getInstance().getView());
	backgroundShader.use();
	glBindTexture(GL_TEXTURE_2D, base_map);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	cubeShader.use();
	for (int i = 0; i < buildings.size();i++) {
		buildings[i].draw();
	}
	edgeShader.use();
	for (int i = 0; i < roads.size(); i++) {
		roads[i].draw_baseLayer();
	}
}

void SchoolMap::adaptation(float a) {
	projection = glm::perspective(FOV, a, 0.1f, 100.0f);
	backgroundShader.setMat4("projection", projection);
	cubeShader.setMat4("projection", projection);
	edgeShader.setMat4("projection", projection);
}

void SchoolMap::loadBuildingData(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line)) {
		if (line == "BEGIN::POI_DATA") break;
	}
	int count = 0;
	std::string name;
	float x, y;
	int node;
	while (std::getline(file, line)) {
		if (line == "END::POI_DATA") break;
		if (line.empty()) continue;
		if (!(count % 2)) {
			name = line;
			//std::cout << " getName:" << line << std::endl;
		} else {
			std::istringstream iss(line);
			std::string part1, part2;
			iss >> node >> x >> y;
			//std::cout << "cord: " << x << " " << y << std::endl;
			buildings.push_back(Building(x, y, node, &cubeShader, name));
		}
		count++;
	}
}

void SchoolMap::addNode(school_map::Node node) {
	nodes.push_back(node);
	schoolRoad.insertVertex(numNode);
	numNode++;
}
void SchoolMap::addEdge(int v1, int v2) {
	if (v1 < 0 || v1 >= numNode || v2 < 0 || v2 >= numNode) return;
	float positions[] = { nodes[v1].x, nodes[v1].y, nodes[v2].x, nodes[v2].y };
	roads.push_back(painter::Edge(positions, 0, v1, v2, v1, &edgeShader));
	schoolRoad.insertEdge(v1, v2, sqrt(pow(nodes[v1].x - nodes[v2].x, 2) + pow(nodes[v1].y - nodes[v2].y, 2)));
}
//------------------------------------------------------------------------
void SchoolMap::loadGraphData(std::string fileName) {
	std::ifstream inFile(fileName);
	std::string line;
	while (std::getline(inFile, line)) {
		if (line == "MinW::undirectedGraph_HEADER: ") break;
	}
	while (std::getline(inFile, line)) {
		if (line == "BEGIN::NODEDATA") break;
	}
	while (std::getline(inFile, line)) {
		if (line == "END::NODEDATA") break;
		school_map::Node temp(line);
		addNode(temp);
	}
	while (std::getline(inFile, line)) {
		if (line == "BEGIN::EDGEDATA") break;
	}
	int v1, v2;
	while (std::getline(inFile, line)) {
		if (line == "END::EDGEDATA") break;
		std::istringstream iss(line);
		iss >> v1 >> v2;
		addEdge(v1, v2);
	}
}

void SchoolMap::navigation() {
	int* lastPoint = nullptr;
	currentDistance = schoolRoad.Dijkstra(buildings[start].node, buildings[target].node, lastPoint);
	for (int i = 0; i < roads.size(); i++) {
		int v1 = roads[i].v1, v2 = roads[i].v2;
		if (lastPoint[v1] == v2 || lastPoint[v2] == v1) roads[i].setColor2(true);
		else roads[i].setColor2(false);
	}
	delete[] lastPoint;
}

void MyGUI::init(GLFWwindow* window) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsClassic();

	ImFont* font = io.Fonts->AddFontFromFileTTF(
		"../imgui/Arial.ttf", 36, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
	);
	IM_ASSERT(font != nullptr);
	io.Fonts->Build();

}

void MyGUI::Render(int width, int height) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	Camera& camera = Camera::getInstance();
	ImGui::SetNextWindowPos(ImVec2(WindowParas::getInstance().SCREEN_WIDTH - width, 0));
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::Begin("Fold");

	ImGui::Dummy(ImVec2(10, 20));
	ImGui::TextWrapped(SchoolMap::getInstance().getCurrentName().c_str());
	ImGui::Dummy(ImVec2(10, 20));
	ImGui::Separator();
	ImGui::Dummy(ImVec2(0, ImGui::GetContentRegionAvail().y - 4.5*ImGui::GetFrameHeight()));
	if (ImGui::Button(camera.getMoving() ? "Rotation Mode" : "Moving Mode", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
		camera.changeMoving();
	}
	if (ImGui::Button("set as start point", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
		SchoolMap::getInstance().setStart();
	}
	if (ImGui::Button("set as end point", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
		SchoolMap::getInstance().setEnd();
	}
	if (ImGui::Button("Confirm", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
		SchoolMap::getInstance().navigation();
	}
	//char buffer[256] = "";
	//ImGui::InputText("Input Field", buffer, sizeof(buffer));
	//std::string textU8 = buffer;

	//ImGui::Checkbox("Show Drag", &isShowDrag);
	//if (isShowDrag)
	//{
	//	float value = 10.0f;
	//	ImGui::DragFloat(u8"Value", &value);
	//}
	//ImGui::SliderFloat("float", &fValue, 0.0f, 1.0f);
	//ImGui::SameLine();
	//ImGui::Text("Value %f", fValue);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}