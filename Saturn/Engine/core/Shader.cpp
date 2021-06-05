#include "Shader.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath)
{
	shader = glCreateProgram();

	ReadShaders(filepath);

	glAttachShader(shader, CompileShader(shadercode.vertexShader, GL_VERTEX_SHADER));
	glAttachShader(shader, CompileShader(shadercode.fragmentShader, GL_FRAGMENT_SHADER));
	glLinkProgram(shader);

	glValidateProgram(shader);
}

void Shader::ReadShaders(const std::string& filepath) {
	std::ifstream file(filepath);
	std::string line;
	std::stringstream shadersource[2];

	enum class mode
	{
		VERTEX = 0,
		FRAGMENT = 1,
		NONE = 2
	};

	mode current = mode::NONE;

	while (std::getline(file, line)) {
		if (line == "#shader vertex") {
			current = mode::VERTEX;
		}
		else if (line == "#shader fragment") {
			current = mode::FRAGMENT;
		}
		else {
			if (current != mode::NONE)
				shadersource[(int)current] << line << std::endl;
		}
	}

	shadercode.vertexShader = shadersource[0].str();
	shadercode.fragmentShader = shadersource[1].str();
}

Shader::~Shader()
{
	glDeleteProgram(shader);
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type) {
	unsigned int id = glCreateShader(type);

	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex " : "fragment ") << "shader!" << std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

int Shader::FindUniformLocation(std::string uniformName)
{
	if (shaderLocationCache.find(uniformName) == shaderLocationCache.end()) {
		int loc = glGetUniformLocation(GetShaderId(), uniformName.c_str());
		if (loc == -1) {
			std::cout << "Uniform " << uniformName << " could not be found!!" << std::endl;
		}
		shaderLocationCache[uniformName] = loc;
		return loc;
	}
	else {
		if (shaderLocationCache[uniformName] == -1) {
			std::cout << "Uniform " << uniformName << " could not be found!" << std::endl;
		}
		return shaderLocationCache[uniformName];
	}
}

void Shader::Bind()
{
	glUseProgram(shader);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

void Shader::SetUniform(std::string uniformName, float f1, float f2, float f3, float f4)
{
	int loc = FindUniformLocation(uniformName);

	glUniform4f(loc, f1, f2, f3, f4);
}

void Shader::SetUniform(std::string uniformName, float f1)
{
	int loc = FindUniformLocation(uniformName);

	glUniform1f(loc, f1);
}

void Shader::SetUniform(std::string uniformName, int i1)
{
	int loc = FindUniformLocation(uniformName);

	glUniform1i(loc, i1);
}

void Shader::SetUniform(std::string uniformName, glm::vec3 v)
{
	int loc = FindUniformLocation(uniformName);

	glUniform3f(loc, v.x, v.y, v.z);
}

void Shader::SetUniform(std::string uniformName, glm::mat4 mat)
{
	int loc = FindUniformLocation(uniformName);

	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}
