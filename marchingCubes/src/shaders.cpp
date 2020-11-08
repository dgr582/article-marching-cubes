//DKE Green | 2020 | https://www.dgr582.com 
//https://www.dgr582.com/articles/2020/marching-cubes

#include "shaders.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int dgr582::prepareShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int newShaderProgram = 0;
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	newShaderProgram = glCreateProgram();
	glAttachShader(newShaderProgram, vertexShader);
	glAttachShader(newShaderProgram, fragmentShader);
	glLinkProgram(newShaderProgram);
	// check for linking errors
	glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(newShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		newShaderProgram = 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return newShaderProgram;
}

