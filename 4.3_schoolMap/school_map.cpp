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

SchoolMap::SchoolMap() : width(0), height(0), nrChannels(0),
	nodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), edgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")),
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

	model = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	projection = glm::perspective(FOV, WindowParas::getInstance().defaultAlpha, 0.1f, 100.0f);
	backgroundShader.setMat4("model", model);
	backgroundShader.setMat4("projection", projection);
	cubeShader.setMat4("model", model);
	cubeShader.setMat4("projection", projection);
	backgroundShader.use();
	glUniform1i(glGetUniformLocation(backgroundShader.ID, "ourTexture"), 0);

	loadData("data.txt");
	buildings.push_back(Building(0, 0, &cubeShader, "??"));
}

void SchoolMap::ProcessInput(GLfloat x, GLfloat y) {
	float realX, realY;
	Camera::getInstance().get2Dxy(x*WindowParas::getInstance().defaultAlpha, y, realX, realY);
	std::cout << realX << " " << realY << std::endl;
}

void SchoolMap::Render() {
	backgroundShader.setMat4("view", Camera::getInstance().getView());
	cubeShader.setMat4("view", Camera::getInstance().getView());
	backgroundShader.use();
	glBindTexture(GL_TEXTURE_2D, base_map);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	cubeShader.use();
	for (int i = 0; i < buildings.size();i++) {
		buildings[i].draw();
	}
}

void SchoolMap::adaptation(float a) {
	projection = glm::perspective(FOV, a, 0.1f, 100.0f);
	backgroundShader.setMat4("projection", projection);
	cubeShader.setMat4("projection", projection);
}

void SchoolMap::loadData(std::string fileName) {
	std::ifstream file(fileName);
	std::string line;
	while (std::getline(file, line)) {
		if (line == "BEGIN::POI_DATA") {
			break;
		}
	}

	int count = 0;
	std::string name;
	float x, y;
	while (std::getline(file, line)) {
		if (line == "END::POI_DATA") break;
		if (line.empty()) continue;
		if (!(count % 2)) {
			name = line;
			std::cout << " getName:" << line << std::endl;
		} else {
			std::istringstream iss(line);
			std::string part1, part2;
			iss >> x >> y;
			//char* endptr;
			//x = std::stof(part1);
			//y = std::stof(part2);
			std::cout << "cord: " << x << " " << y << std::endl;
			buildings.push_back(Building(x, y, &cubeShader, name));
		}
		count++;
	}
}

void MyGUI::init(GLFWwindow* window) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330"); // 使用适合你环境的着色器版本字符串
	ImGui::StyleColorsClassic();

	ImFont* font = io.Fonts->AddFontFromFileTTF(
		"../imgui/Arial.ttf", 46, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()
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
	ImGui::Begin("Drag Button");
	if (ImGui::Button(camera.getRotation() ? "Disable Rotation" : "Enable Rotation")) {
		camera.changeRotation();
		if (!camera.getRotation()) camera.init();
	}
	ImGui::Text("A Text String");

	char buffer[256] = "";
	ImGui::InputText("Input Field", buffer, sizeof(buffer));
	std::string textU8 = buffer;

	ImGui::Checkbox("Show Drag", &isShowDrag);
	if (isShowDrag)
	{
		float value = 10.0f;
		ImGui::DragFloat(u8"Value", &value);
	}
	ImGui::SliderFloat("float", &fValue, 0.0f, 1.0f);
	ImGui::SameLine();
	ImGui::Text("Value %f", fValue);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}