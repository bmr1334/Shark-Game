//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <string>
#include <vector>
#include <freeImage.h>

#include <GL/glew.h>        //don't switch these
#include <GLFW/glfw3.h>     //don't switch these

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Object.h"

using namespace glm;

struct Vertex { vec3 location; vec2 uv; vec3 normal; };
struct VertInd { unsigned int locInd; unsigned int uvInd; unsigned int normInd; };

#pragma once
class Model : Object{
private:
	//private variables
	GLuint vertArr;
	GLuint vertBuf;
	std::vector<Vertex> vertBufData;
	unsigned int vertCount = 0;
	std::vector<VertInd> verts;
public:
	//public variables
	unsigned int texID;
	Transform trans = Transform();

	//sets values of vertArr and vertBuf
	Model();

	//holds buffer model code
	bool Buffer(std::string objFile);

	//draw model(s) on screen
	void Render();

	//loads model textures
	bool Texture(char* textFile);

	~Model();
};