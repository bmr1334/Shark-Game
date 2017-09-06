#pragma once

#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader{
public:
	//variables
	GLuint program, vprogram, fprogram;
	std::string filenamev = "Shaders/vShader.glsl";
	std::string filenamef = "Shaders/fShader.glsl";

	//these do nothing
	Shader();
	~Shader();

	//load shaders, sets value of programs to 0 if loading fails
	//something other than 0 if loading succeeds
	bool load();

	//helper method used by load() to read and compile a shader file
	bool compile(GLenum shaderType);

	//calls glUseProgram(program)
	void use();

	//deallocates this shader's/program's memory from GPU
	void unload();
};

