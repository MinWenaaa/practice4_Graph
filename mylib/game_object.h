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
const int stride_node = circle_pointNum + 2;
const int stride_line = 4;

namespace painter {

	class Node {
	public:
		Node(){}
		Node(GLfloat x, GLfloat y, GLuint color, Shader* shader, GLenum shp = GL_TRIANGLE_FAN, GLfloat pocess = 0.01);
		//Node(const Node& other) : gameObject(other.vertices, other.shape, other.shader), radius(other.radius) {}
		void draw_baseLayer();
		void draw_coverLayer(float &p);
		void setCoverColor(GLuint color);

		~Node() {	// Attention: 析构函数调用时机未知，导致VAO失效
			// glDeleteVertexArrays(1, &VAO);
			// glDeleteBuffers(1, &VBO_position);
			// glDeleteBuffers(1, &VBO_color);
		}

		GLuint VAO, VAO_cover, VBO_position, VBO_color, coverVBO_p, coverVBO_c, color, newColor;
		Shader* shader;
		GLfloat x, y;
		int depth = 0;

	private:
		bool isInited;
		float pocess;							// 绘制过程中变化
		void getArc(GLfloat* data, float p);
		void setColor();
	};

	class Edge {
	public:
		Edge(){}
		Edge(GLfloat* positions, GLint color, int v1, int v2, int satrt, Shader* shader = nullptr);

		~Edge() {
			//glDeleteVertexArrays(1, &VAO);
			//glDeleteBuffers(1, &VBO);
		}
		void draw_baseLayer();
		void draw_coverLayer(float &p);
		void setCoverColor(GLuint color);

		int v1, v2;
		GLfloat node[4];						// 节点坐标
		int start;								// 记录绘制起点
		Shader* shader;
		GLuint VAO, VAO_cover, VBO_position, VBO_color, coverVBO_p, coverVBO_c, color, newColor;
		int depth = 0;

	private:
		bool isInited;
		float poccess;		// 绘制过程中变化
		GLfloat delta;
		void transform(GLfloat* data, float p);
		void setColor();
	};

}
