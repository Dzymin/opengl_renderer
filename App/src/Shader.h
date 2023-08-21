#pragma once
#include "glad/glad.h"
#include "pch.h"

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	Shader(const Shader& other) = delete;
	Shader(Shader&& other) = delete;
	Shader& operator=(const Shader& other) = delete;
	Shader& operator=(Shader&& other) = delete;

	void Bind() const;
	void Unbind() const;
private:
	uint32_t m_Program;

private:
	std::string ReadShaderSource(const std::string& shaderPath);
	void CompileShader(uint32_t shader, const char* source);
};
