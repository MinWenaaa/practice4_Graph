//
//-------------------- for the practice4_Graph ----------------------
//
#pragma once

#include<shader.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<vector>

namespace painter {

	class gameObject {
	public:
		gameObject(const std::vector<glm::vec2> positions, GLenum shp, Shader* shader);
		gameObject(const glm::vec2 position, GLenum shp, Shader* shader);
		gameObject(const gameObject&) = delete;
		void operator=(const gameObject&) = delete;
		~gameObject() {
			delete[] vertices;
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		virtual void draw() const {}

		GLuint VAO, VBO;
		Shader* shader;
		GLenum shape;
		GLsizei stride;
		GLfloat* vertices;
	};

	class Node : public gameObject {
	public:
		Node(const std::vector<glm::vec2> positions = std::vector<glm::vec2>(0), GLenum shp = GL_LINE, Shader* shader = nullptr) :gameObject(positions, shp, shader) {}
		void draw() const override {}
	};

	class Edge : public gameObject {
	public:
		Edge(const glm::vec2 positions = glm::vec2(0.0f, 0.0f), GLenum shp = GL_LINE, Shader* shader = nullptr) :gameObject(positions, shp, shader) {}
		void draw() const override {}
	};

}
