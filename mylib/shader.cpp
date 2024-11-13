//
//-------------------- for the practice4_Graph ----------------------
//

#include"shader.h"
#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cout << "ERROR::shader_file_not_succesfully_read" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "vertex");
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "fragment");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "program");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	//std::cout << glGetError() << std::endl;
}
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "program"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::shader_compilation_error of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::program_linking_error of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
// ------------------------------------------------------------------------
void Shader::use() {
	//std::cout << glGetError() << std::endl;
	glUseProgram(ID);
	//std::cout << glGetError() << std::endl;
}
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, float f1, float f2) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), f1, f2);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, float f1, float f2, float f3) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, float f1, float f2, float f3, float f4) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), f1, f2, f3, f4);
}

WindowParas::WindowParas() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL_Learning", NULL, NULL);

	if (window == NULL) {
		std::cout << "Wrong!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Wrong!" << std::endl;
	}
	defaultAlpha = SCREEN_WIDTH / SCREEN_HEIGHT;
	//std::cout << glGetError() << std::endl;
}
// ------------------------------------------------------------------------
GLfloat WindowParas::screen2normalX(GLdouble screenX) const {
	return  (2.0f * static_cast<GLfloat>(screenX / SCREEN_WIDTH * xScale)) - 1.0f;
}
GLfloat WindowParas::screen2normalY(GLdouble screenY) const {
	return 1.0f - (2.0f * static_cast<GLfloat>(screenY / SCREEN_HEIGHT * yScale));
}
GLfloat WindowParas::normal2orthoX(GLfloat normalX) const {
	GLfloat left = -SCREEN_WIDTH / xScale / 2.0f;
	GLfloat right = SCREEN_WIDTH / xScale / 2.0f;
	return  left + (right - left) * (normalX + 1) / 2;
}
GLfloat WindowParas::normal2orthoY(GLfloat normalY) const {
	GLfloat button = -SCREEN_HEIGHT / yScale / 2.0f;
	GLfloat top = SCREEN_HEIGHT / yScale / 2.0f;
	return  button + (top - button) * (normalY + 1) / 2;
}
// ------------------------------------------------------------------------
