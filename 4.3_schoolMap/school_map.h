//
//-------------------- for the 4.3_schoolMap ----------------------
//

#pragma once
#include<GLFW/glfw3.h>
#include"shader.h"

class SchoolMap {
public:
	static SchoolMap& getInstance() {
		static SchoolMap instance;
		return instance;
	}
	SchoolMap(const SchoolMap&) = delete;
	SchoolMap& operator=(const SchoolMap&) = delete;

	void ProcessInput(GLfloat x, GLfloat y);
	void ProcessMouseScroll(float yoffset, float xpos, float ypos);
	void ProcessMouseDrag(float xpos, float ypos);
	void Render();

	void initCursorPos(float xpos, float ypos);

private:
	SchoolMap();
	void upDateRotationMatrix();

	GLuint base_map, VAO, VBO, EBO;
	int width, height, nrChannels;		// ��ͼӰ��ĳ����

	Shader nodeShader, edgeShader, backgroundShader;

	GLfloat Zoom;						// ���ű���
	GLfloat offset[2];					// ƫ��
	GLfloat lastxpos, lastypos;
	GLfloat pitch, yaw;					// �����Ǻ�ƫ����
	glm::mat4 rotationMatrix;			// ��ת����
};
