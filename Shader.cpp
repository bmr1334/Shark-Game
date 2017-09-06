#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>

//variables
GLuint shaderIndex;

//constructors do nothing
Shader::Shader(){
}
Shader::~Shader(){
}

//loads shaders
bool Shader::load(){
	//variables
	GLint lengthOfLog;

	//call compile() for success check
	bool vertCheck = compile(GL_VERTEX_SHADER);
	bool fragCheck = compile(GL_FRAGMENT_SHADER);

	//if either compile failed, there was an error, so return false
	if (!vertCheck || !fragCheck) {
		return false;
	}

	//create shader program, save the result in the member data, program
	program = glCreateProgram();

	//attach both shaders -- I'm assuming this attaches the vert/frag shaders to the main program
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);

	//link program with glLinkProgram(program) -- then links it all together
	glLinkProgram(program);

	//if program linked correcly, return true
	GLint shaderSuccess;
	glGetProgramiv(program, GL_LINK_STATUS, &shaderSuccess);
	if (shaderSuccess != 0) {
		return true;
	}

	//if link failed, get error log and print out
	else {
		//get log length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &lengthOfLog);

		//create char array to hold log
		char logData[] = "";

		//store log into char array
		glGetProgramInfoLog(program, (int)lengthOfLog, 0, logData);

		//print log info
		std::cout << "\n";
		for (int i = 0; i < strlen(logData); i++) {
			std::cout << logData[i];
		}
		std::cout << std::endl;

		//delete the program and log char array, then return false
		glDeleteProgram(program);
		delete[] logData;
		return false;
	}
}

//compiles shaders
bool Shader::compile(GLenum shaderType){
	//variables
	GLint shaderSuccessResult;
	std::string filename;

	//HAS to be before error check to make sure file names are assigned properly.
	if (shaderType == GL_VERTEX_SHADER) {
		filename = filenamev;
	}
	if (shaderType == GL_FRAGMENT_SHADER) {
		filename = filenamef;
	}

	//open vertex/fragment shader file
	std::ifstream instream(filename, std::ios::binary);

	//if problem occurs, print error message and return zero
	if (!instream.is_open()) {
		std::cout << filename << " didn't open correctly. Shame on you." << std::endl;
		return 0;
	}

	//get length of file
	instream.seekg(0, std::ios::end);
	int length = instream.tellg();
	instream.seekg(0, std::ios::beg);

	//load text into null-terminated char array
	char* shaderHolder = new char[length + 1];
	shaderHolder[length] = '\0';
	instream.read(shaderHolder, length);
	instream.close();

	//std::istream(filenamev);
	if (shaderType == GL_VERTEX_SHADER) {
		//get index of the shader object
		vprogram = glCreateShader(shaderType);

		//delete[] char array from last step, and call shader methods
		glShaderSource(vprogram, 1, &shaderHolder, 0);
		glCompileShader(vprogram);
		delete[] shaderHolder;

		//find out if shader compilation worked
		glGetShaderiv(vprogram, GL_COMPILE_STATUS, &shaderSuccessResult);

		//if it did, return true
		if (shaderSuccessResult != 0) {
			return true;
		}

		//if it didn't, get info log
		else {
			//called to get the length
			GLint logLength;
			glGetShaderiv(vprogram, GL_INFO_LOG_LENGTH, &logLength);

			//store info log in logData for printout
			GLchar* logData = new GLchar[logLength];
			glGetShaderInfoLog(vprogram, logLength, 0, logData);

			//print out shader log info stored in logData
			std::cout << logData << std::endl;

			//delete shader and log array, then return false
			glDeleteShader(vprogram);
			delete[]logData;
			return false;
		}
	}

	if (shaderType == GL_FRAGMENT_SHADER) {
		//get index of the shader object
		fprogram = glCreateShader(shaderType);

		//delete[] char array from last step, and call shader methods
		glShaderSource(fprogram, 1, &shaderHolder, 0);
		glCompileShader(fprogram);
		delete[] shaderHolder;

		//find out if shader compilation worked
		glGetShaderiv(fprogram, GL_COMPILE_STATUS, &shaderSuccessResult);

		//if it did, return true
		if (shaderSuccessResult != 0) {
			return true;
		}

		//if it didn't, get info log
		else {
			//called to get the length
			GLint logLength;
			glGetShaderiv(fprogram, GL_INFO_LOG_LENGTH, &logLength);

			//store info log in logData for printout
			GLchar* logData = new GLchar[logLength];
			glGetShaderInfoLog(fprogram, logLength, 0, logData);

			//print out shader log info stored in logData
			std::cout << logData << std::endl;

			//delete shader and log array, then return false
			glDeleteShader(fprogram);
			delete[]logData;
			return false;
		}
	}
}

//uses 'program' -- pretty self explanatory
void Shader::use(){
	glUseProgram(program);
}

//deallocates program and shader memory from GPU
void Shader::unload(){
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);
}