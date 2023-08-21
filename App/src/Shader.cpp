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
