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
	int width, height, nrChannels;		// µ×Í¼Ó°ÏñµÄ³¤¿í¸ß

	Shader nodeShader, edgeShader, backgroundShader;

	GLfloat Zoom;						// Ëõ·Å±ÈÀý
	GLfloat offset[2];					// Æ«ÒÆ
	GLfloat lastxpos, lastypos;
	GLfloat pitch, yaw;					// ¸©Ñö½ÇºÍÆ«º½½Ç
	glm::mat4 rotationMatrix;			// Ðý×ª¾ØÕó
};
