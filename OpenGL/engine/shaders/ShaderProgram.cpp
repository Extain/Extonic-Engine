#include "ShaderProgram.h"

namespace Extonic {
	ShaderProgram::ShaderProgram()
	{

	}

	void ShaderProgram::createDefaultShader()
	{
		createShader(vertexShaderSource, fragmentShaderSource);

	}

	void ShaderProgram::createShader(const char* vs, const char* fs)
	{
		int vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vs, NULL);
		glCompileShader(vertexID);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "SHADER::VERTEX::COMPILED::SUCCESSFULLY" << std::endl;
		}

		int fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &fs, NULL);
		glCompileShader(fragmentID);

		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "SHADER::FRAGMENT::COMPILED::SUCCESSFULLY" << std::endl;
		}

		this->shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexID);
		glAttachShader(shaderID, fragmentID);
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKED_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			std::cout << "SHADER::PROGRAM::LINKED::SUCCESSFULLY" << std::endl;
		}
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}

	void ShaderProgram::uniform4f(const std::string& uniform, glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(this->shaderID, uniform.c_str()), 1, &value[0]);
	}

	void ShaderProgram::uniform4f(const std::string& uniform, float x, float y, float z, float a)
	{
		glUniform4f(glGetUniformLocation(this->shaderID, uniform.c_str()), x, y, z, a);
	}

	void ShaderProgram::matrix4f(const std::string& uniform, glm::mat4& value)
	{
		//glUniformMatrix4fv(glGetUniformLocation(this->shaderID, uniform.c_str()), &value[0]);
	}


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(shaderID);
	}
}
