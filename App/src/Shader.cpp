#include "pch.h"
#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	m_Program = glCreateProgram();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexSource = ReadShaderSource(vertexPath);
	std::string fragmentSource = ReadShaderSource(fragmentPath);

	CompileShader(vertexShader, vertexSource.c_str());
	CompileShader(fragmentShader, fragmentSource.c_str());

	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);

	int success;
	char infoLog[512];

	glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
		std::cout << "Failed to link shader program: " << infoLog << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
}

void Shader::Bind() const
{
	glUseProgram(m_Program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1f(const char* name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform2f(const char* name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const char* name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const char* name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform2i(const char* name, int v0, int v1)
{
	glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3i(const char* name, int v0, int v1, int v2)
{
	glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4i(const char* name, int v0, int v1, int v2, int v3)
{
	glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1u(const char* name, uint32_t v0)
{
	glUniform1ui(GetUniformLocation(name), v0);
}

void Shader::SetUniform2u(const char* name, uint32_t v0, uint32_t v1)
{
	glUniform2ui(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3u(const char* name, uint32_t v0, uint32_t v1, uint32_t v2)
{
	glUniform3ui(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4u(const char* name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
{
	glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3);
}

std::string Shader::ReadShaderSource(const std::string& shaderPath)
{
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		return shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to read shader source: " << shaderPath << std::endl;
		return "";
	}
}

void Shader::CompileShader(uint32_t shader, const char* source)
{
	int success;
	char infoLog[512];

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "Failed to compile shader: " << infoLog << std::endl;
	}
}

int Shader::GetUniformLocation(const char* name)
{
	int location = glGetUniformLocation(m_Program, name);
	if (location == -1)
	{
		std::cout << "Failed to find corresponding uniform variable: " << name << std::endl;
	}

	return location;
}
