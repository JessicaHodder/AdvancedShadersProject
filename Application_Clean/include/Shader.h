#pragma once
#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>


/*
  Compiles and links shader code form files
  Pass file locations as constructor parameters
  A bunch of setters for uniforms
*/

class Shader
{
public:

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* controlPath = nullptr, const char* evaluationPath = nullptr);
	void use();
	inline unsigned int getID() const { return ID; }
	// utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
	void setUniformBlock(const std::string& name, unsigned int uniformBlock) const;

private:
	void checkCompileErrors(GLuint shader, std::string type);
	unsigned int ID;

};
#endif

