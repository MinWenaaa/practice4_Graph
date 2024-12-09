//
//-------------------- for the practice4_Graph ----------------------
//

#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<vector>
#include<string>

const float FOV = glm::radians(60.f);
const float f = 1 / tan(FOV / 2);

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
	void setMat4(const std::string& name, const glm::mat4& mat) const;
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

	void setRatio(GLfloat ratio) {
		aspectRatio = ratio; 
		updateScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	void updateScreenSize(GLint width, GLint height);

	GLFWwindow* window;
	GLint SCREEN_WIDTH = 1600, SCREEN_HEIGHT = 1200;
	GLfloat aspectRatio = 1;
	GLint displayWidth, displayHeight;
	GLfloat xScale = 1, yScale = 1;
	GLfloat defaultAlpha;

	GLfloat screen2normalX(GLdouble screenX) const;
	GLfloat screen2normalY(GLdouble screenY) const;
	GLfloat normal2orthoX(GLfloat normalX) const;
	GLfloat normal2orthoY(GLfloat normalY) const;
	
private:
	WindowParas();
};

const double PI = 3.1415926;
class Camera {
public:
	static Camera& getInstance() {
		static Camera instance;
		return instance;
	}
	Camera(const Camera&) = delete;
	void operator=(const Camera&) = delete;

	glm::mat4 getView() {
		return view;
	}

	void changeZoom(float zoom) { distance -= zoom; upDatePos(); }
	void changeAzimation(float delta) { azimuthAngle += delta; upDatePos(); }
	void changeElevation(float delta) {		// ��ʱ�ر��ӽ���ת
		//elevationAngle += delta;
		if (elevationAngle > (PI / 2)) elevationAngle = PI / 2;
		if (elevationAngle < 0.4f) elevationAngle = 0.4f;
		upDatePos();
	}

	void get2Dxy(float oX, float oy, float& rX, float& rY);


private:
	Camera(): distance(2.f), elevationAngle(0.6f), azimuthAngle(0.f), cameraTarget(glm::vec3(0.f,0.f,0.f)) {
		upDatePos();
	}

	void upDatePos() {
		GLfloat plant = distance * cos(elevationAngle);
		cameraPos = glm::vec3(plant*sin(azimuthAngle), distance * sin(elevationAngle), plant * cos(azimuthAngle));
		view = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	GLfloat distance, elevationAngle, azimuthAngle;
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::mat4 view;

};

#endif
