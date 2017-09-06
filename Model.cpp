//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Model.h"

//sets initial transform struct values from object.h
Model::Model(){
	vertArr = 0;
	vertBuf = 0;
	trans.location = { 0,0,0 };
	trans.rotation = { 0,0,0 };
	trans.size = { 1,1,1 };
	trans.velocity = { 0,0,0 };
	trans.force = { 0,0,0 };
	trans.mass = 0;
}

//buffers in models
bool Model::Buffer(std::string objFile){
	//variables
	std::vector<glm::vec3> locations;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::ifstream file(objFile);
	std::string line;
	std::string label;
	float first, second, third;
	unsigned int one, two, three;
	char slash = '/';
	
	//loop to get vertex locations, uvs, normals
	while (file.eof() == false) {
		//get line info
		getline(file, line);
		std::istringstream ss(line);

		//get line label
		ss >> label;

		//perform different calculations based on label value
		if (label == "v") { //locations
			//get float values
			ss >> first >> second >> third;

			//add values to locations vector
			locations.push_back(glm::vec3(first, second, third));
		}
		else if (label == "vt") { //uvs
			//get float values
			ss >> first >> second >> third;

			//add values to uvs vector
			uvs.push_back(glm::vec2(first, second));
		}
		else if (label == "vn") { //normals
			//get float values
			ss >> first >> second >> third;

			//add values to normals vector
			normals.push_back(glm::vec3(first, second, third));
		}

		//get indices
		else if (label == "f") {
			for (int i = 0; i < 3; i++) {
				//get values
				ss >> one >> slash >> two >> slash >> three;
				
				//decrement values
				one--;
				two--;
				three--;

				//store values in VertInd
				VertInd temp;
				temp.locInd = one;
				temp.uvInd = two;
				temp.normInd = three;

				//add values to verts
				verts.push_back(temp);

				//increment vertCount -- used to determine when to close file
				vertCount++;
			}
		}
	}
	
	//close file
	file.close();

	//iterate over indices, filling vertex buffer with vertices
	vertBufData.resize(vertCount);
	for (size_t i = 0; i < verts.size(); i++) {
			vertBufData[i] = {
			locations[verts[i].locInd],
			uvs[verts[i].uvInd],
			normals[verts[i].normInd]
		};
	}

	//generate array and buffer (same as in main)
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	//bind array and buffer (same as in main)
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//upload model data
	//store data in vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verts.size(), &vertBufData[0], GL_STATIC_DRAW);

	//set up location attribute
	glEnableVertexAttribArray(0); //attribute index - 0
	glVertexAttribPointer(
		0,                   //attribute index - 0 in this case
		3,                   //number of components (x,y,z)
		GL_FLOAT,            //type of data
		GL_FALSE,            //should we normalize the data?
		sizeof(Vertex),      //stride (bytes per vertex)
		0);                  //offset to this attribute

	//set up uv attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(float) * 3)); //offset to this attribute - skips this many (3) locations

	//set up normal attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(float) * 5)); //offset to this attribute - skips this many (5) locations

	glBindVertexArray(0);

	return true;
}

//renders models
void Model::Render()
{
	//render game objects
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);

	//bind desired texture while drawing it
	glBindTexture(GL_TEXTURE_2D, texID);
}

//uses texFile as the texture
bool Model::Texture(char * texFile)
{
	//load texures before game loop
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(texFile, 0), texFile);

	//did the loading fail?
	if (image == nullptr) {
		return false;
	}

	//convert original image to 32bit bmp
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);

	//unload original image from memory
	FreeImage_Unload(image);

	//generate and bind a new texture
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//upload texture bytes
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));

	//set min filter to 'linear' instead of 'mipmap linear'
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//clear texture from RAM (not VRAM)
	FreeImage_Unload(image32Bit);

	//unbind the texture when finished uploading
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return true;
}

Model::~Model(){
}