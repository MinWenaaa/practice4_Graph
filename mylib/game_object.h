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
		Node(GLfloat x, GLfloat y, Shader* shader, GLenum shp = GL_TRIANGLE_FAN, GLfloat radius = 0.01);
		//Node(const Node& other) : gameObject(other.vertices, other.shape, other.shader), radius(other.radius) {}
		void draw() ;

		~Node() {
			//if (vertices)
			//	delete[] vertices;
			//glDeleteVertexArrays(1, &VAO);
			//glDeleteBuffers(1, &VBO);
		}

		GLfloat* getArc(GLfloat x, GLfloat y, GLfloat radius, GLfloat*& data);
		bool getIsMoving() { return moving; }

		GLfloat radius;
		GLuint VAO, VBO;
		Shader* shader;
		GLsizei stride;
		GLfloat x, y;
		GLfloat* data;
		bool moving;
	};

	class Edge {
	public:
		Edge(){}
		Edge(GLfloat* positions, int v1, int v2, Shader* shader = nullptr, int stride = 4);

		~Edge() {}
		void draw();
		void transform();

		GLfloat* node;	// [0]�ڵ�1;[1:2]�ڵ�1����;[3]�ڵ�2;[4:5]�ڵ�2����
		int start;		// ��¼�������
		GLfloat* vertices;
		Shader* shader;
		GLuint VAO, VBO1, VBO2;
		int stride;
		bool moving;
		float poccess;
	};

}
