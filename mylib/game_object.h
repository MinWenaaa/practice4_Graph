//
//-------------------- for the practice4_Graph ----------------------
//
#pragma once

#include<shader.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<vector>

namespace painter {

	class Node {
	public:
		Node(){}
		Node(GLfloat x, GLfloat y, Shader* shader, GLenum shp = GL_TRIANGLE_FAN, GLfloat radius = 0.1);
		//Node(const Node& other) : gameObject(other.vertices, other.shape, other.shader), radius(other.radius) {}
		void draw() const;

		~Node() {
			//if (vertices)
			//	delete[] vertices;
			//glDeleteVertexArrays(1, &VAO);
			//glDeleteBuffers(1, &VBO);
		}

		GLfloat* getArc(GLfloat x, GLfloat y, GLfloat radius);

		GLfloat radius;
		GLuint VAO, VBO;
		Shader* shader;
		GLsizei stride;
		GLfloat* vertices;
	};

	class Edge {
	public:
		Edge(){}
		Edge(GLfloat* positions, Shader* shader = nullptr, int stride = 4);

		~Edge() {}
		void draw() const;

		GLfloat* vertices;
		Shader* shader;
		GLuint VAO, VBO;
		int stride;
	};

}
