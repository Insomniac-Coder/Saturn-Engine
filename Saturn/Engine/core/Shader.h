#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind();
	void UnBind();

	void SetUniform(std::string uniformName, float f1, float f2, float f3, float f4);
	void SetUniform(std::string uniformName, float f1);
	void SetUniform(std::string uniformName, int i1);
	void SetUniform(std::string uniformName, glm::mat4 mat);
	void SetUniform(std::string uniformName, glm::vec3 v);

private:
	struct shaders
	{
		std::string vertexShader;
		std::string fragmentShader;
	} shadercode;

	std::unordered_map<std::string, unsigned int> shaderLocationCache;

	void ReadShaders(const std::string& filepath);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int shader;
	inline unsigned int GetShaderId() { return shader; }
	int FindUniformLocation(std::string uniformName);
};

#endif SHADER_H