#include "ShaderProgram.h"

namespace Extonic {
	ShaderProgram::ShaderProgram()
	{
		loadShader();
	}

	void ShaderProgram::loadShader()
	{
		int vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vertexShaderSource, NULL);
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
		glShaderSource(fragmentID, 1, &fragmentShaderSource, NULL);
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


	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(shaderID);
	}
}
