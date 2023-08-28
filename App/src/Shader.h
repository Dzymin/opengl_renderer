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

	void SetUniform1f(const char* name, float v0);
	void SetUniform2f(const char* name, float v0, float v1);
	void SetUniform3f(const char* name, float v0, float v1, float v2);
	void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);
	
	void SetUniform1i(const char* name, int v0);
	void SetUniform2i(const char* name, int v0, int v1);
	void SetUniform3i(const char* name, int v0, int v1, int v2);
	void SetUniform4i(const char* name, int v0, int v1, int v2, int v3);
	
	void SetUniform1u(const char* name, uint32_t v0);
	void SetUniform2u(const char* name, uint32_t v0, uint32_t v1);
	void SetUniform3u(const char* name, uint32_t v0, uint32_t v1, uint32_t v2);
	void SetUniform4u(const char* name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);

private:
	uint32_t m_Program;

private:
	std::string ReadShaderSource(const std::string& shaderPath);
	void CompileShader(uint32_t shader, const char* source);

	int GetUniformLocation(const char* name);
};
