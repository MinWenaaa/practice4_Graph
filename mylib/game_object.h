//
//-------------------- for the practice4_Graph ----------------------
//
#pragma once

#include<shader.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<vector>

const double PI = 3.14159265358979323846;
const int circle_pointNum = 30;

namespace painter {

	class Node {
	public:
		Node(){}
		Node(GLfloat x, GLfloat y, GLint color, Shader* shader, GLenum shp = GL_TRIANGLE_FAN, GLfloat pocess = 0.01);
		//Node(const Node& other) : gameObject(other.vertices, other.shape, other.shader), radius(other.radius) {}
		void draw() ;

		~Node() {	// Attention: ������������ʱ��δ֪������VAOʧЧ
			// glDeleteVertexArrays(1, &VAO);
			// glDeleteBuffers(1, &VBO_position);
			// glDeleteBuffers(1, &VBO_color);
		}

		void getArc(GLfloat* data);
		bool getIsMoving() { return isDrawing; }

		GLuint VAO, VBO_position, VBO_color;
		GLint color;
		Shader* shader;
		GLfloat x, y;

		bool isDrawing;
		float pocess;							// ���ƹ����б仯
	};

	class Edge {
	public:
		Edge(){}
		Edge(GLfloat* positions, GLint color, int v1, int v2, int satrt, Shader* shader = nullptr);

		~Edge() {
			//glDeleteVertexArrays(1, &VAO);
			//glDeleteBuffers(1, &VBO);
		}
		void draw();
		void transform(GLfloat* data);

		int v1, v2;
		GLfloat node[4];						// �ڵ�����
		int start;								// ��¼�������
		Shader* shader;
		GLuint VAO, VBO_position, VBO_color, color;
		bool isDrawing;
		float poccess;							// ���ƹ����б仯

	private:
		GLfloat delta;
	};

}
