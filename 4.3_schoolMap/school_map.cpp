#include<glad/glad.h>
#include"school_map.h"
#include<stb_image.h>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

SchoolMap::SchoolMap() : width(0), height(0), nrChannels(0), Zoom(1.0), offset{ 0.0, 0.0 }, pitch(0.8), yaw(0.8), rotationMatrix(glm::mat4(1.0f)),
	nodeShader(Shader("../mylib/node_static.vs", "../mylib/node_static.fs")), edgeShader(Shader("../mylib/edge_basic.vs", "../mylib/edge_basic.fs")),
	backgroundShader(Shader("../mylib/background.vs", "../mylib/background.fs")) {

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
			1.0f, 1.0f,     1.0f, 1.0f,  
			1.0f, -1.0f,    1.0f, 0.0f,  
			-1.0f, -1.0f,   0.0f, 0.0f,  
			-1.0f, 1.0f,    0.0f, 1.0f   };
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	upDateRotationMatrix();

	backgroundShader.use();
	glUniform1i(glGetUniformLocation(backgroundShader.ID, "ourTexture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(backgroundShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	backgroundShader.setFloat("zoom", Zoom);
	backgroundShader.setVec2("offset", offset[0], offset[1]);

}

void SchoolMap::ProcessInput(GLfloat x, GLfloat y) {

}

void SchoolMap::ProcessMouseScroll(float yoffset, float xpos, float ypos) {
	Zoom += yoffset * 0.1;
	if (Zoom < 0.8) Zoom = 0.8;
	offset[0] += xpos * yoffset * 0.02;
	offset[1] += ypos * yoffset * 0.02;
	backgroundShader.setFloat("zoom", Zoom);
	backgroundShader.setVec2("offset", offset[0], offset[1]);
	std::cout << yoffset << std::endl;
}

void SchoolMap::ProcessMouseDrag(float xpos, float ypos) {
	pitch = 
	yaw =  -(lastypos - ypos) * 0.001;

	lastxpos = xpos;
	lastypos = ypos;

	//std::cout << "Pocess Dragging:" << pitch << ", " << yaw;
	
	upDateRotationMatrix();
	//rotationMatrix = glm::rotate(rotationMatrix, pitch, glm::vec3(0, 1, 0));
	backgroundShader.use();
	glUniformMatrix4fv(glGetUniformLocation(backgroundShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
}

void SchoolMap::Render() {
	glBindTexture(GL_TEXTURE_2D, base_map);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SchoolMap::initCursorPos(float xpos, float ypos) {
	lastxpos = xpos;
	lastypos = ypos;
}

void SchoolMap::upDateRotationMatrix() {
	rotationMatrix = glm::rotate(rotationMatrix, pitch, glm::vec3(0, 1, 0));
	rotationMatrix = glm::rotate(rotationMatrix, yaw, glm::vec3(1, 0, 0));
}