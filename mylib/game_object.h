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

		GLfloat* node;	// [0]节点1;[1:2]节点1坐标;[3]节点2;[4:5]节点2坐标
		int start;		// 记录绘制起点
		GLfloat* vertices;
		Shader* shader;
		GLuint VAO, VBO1, VBO2;
		int stride;
		bool moving;
		float poccess;
	};

}
