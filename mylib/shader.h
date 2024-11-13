//
//-------------------- for the practice4_Graph ----------------------
//

#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<vector>
#include<string>

class Shader {
public:
	GLuint ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, float f1, float f2) const;
	void setVec3(const std::string& name, float f1, float f2, float f3) const;
	void setVec4(const std::string& name, float f1, float f2, float f3, float f4) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

class WindowParas {
public:
	static WindowParas& getInstance() {
		static WindowParas instance;
		return instance;
	}
	WindowParas(const WindowParas&) = delete;
	void operator=(const WindowParas&) = delete;

	GLFWwindow* window;
	const GLint WINDOW_WIDTH = 960;
	const GLint WINDOW_HEIGHT = 720;
	const GLint SIDEBAR_WIDTH = 300;
	GLint SCREEN_WIDTH = 1600, SCREEN_HEIGHT = 1200;
	GLfloat xScale = 1, yScale = 1;
	GLfloat defaultAlpha;

	GLfloat screen2normalX(GLdouble screenX) const;
	GLfloat screen2normalY(GLdouble screenY) const;
	GLfloat normal2orthoX(GLfloat normalX) const;
	GLfloat normal2orthoY(GLfloat normalY) const;
	
private:
	WindowParas();
};

#endif
