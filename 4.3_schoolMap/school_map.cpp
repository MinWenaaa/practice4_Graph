#include<glad/glad.h>
#include"school_map.h"
#include<stb_image.h>

SchoolMap::SchoolMap(): width(0), height(0), nrChannels(0), 
	nodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), edgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")),
	backgroundShader(Shader("../mylib/background.vs", "../mylib/background.fs")) {

	unsigned char* data = stbi_load("UAVimagery.jpg", &width, &height, &nrChannels, 0);
	glGenTextures(1, &base_map);
	glBindTexture(GL_TEXTURE_2D, base_map);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	float vertices[] = {
			1.0f, 1.0f,     1.0f, 1.0f,  
			1.0f, -1.0f,    1.0f, 0.0f,  
			-1.0f, -1.0f,   0.0f, 0.0f,  
			-1.0f, 1.0f,    0.0f, 1.0f   
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void SchoolMap::Init(GLFWwindow* window) {
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, mouseCallback);
}

void SchoolMap::ProcessInput(GLfloat x, GLfloat y) {

}

void SchoolMap::Render() {
	glBindTexture(GL_TEXTURE_2D, base_map);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {

}