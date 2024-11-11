#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>

class Shader {
public:
	unsigned int ID;

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

#endif
