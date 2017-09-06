//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <iostream>
#include <vector>

#include <GL/glew.h>        //don't switch these
#include <GLFW/glfw3.h>     //don't switch these

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <FreeImage.h>
#include "Shader.h"
#include "Camera.h"
#include "Engine.h"
#include "Model.h"
#include "myobj.h"

using namespace glm;

int main() {
	//variables
	Engine eng = Engine(); //instance of Engine class

	//start engine
	eng.Start();

	//load all assets, check for failure
	if (eng.bufferModels() == true) {
		std::cout << "Models were buffered successfully" << std::endl;
	}
	else {
		std::cout << "Models were NOT buffered!" << std::endl;
	}

	//game loop, loops until user presses escape
	while (!glfwGetKey(eng.GLFWwindowPtr ,GLFW_KEY_ESCAPE)) { //press escape to exit

		//update engine
		eng.Update();
	}

	//stop engine
	eng.Stop();
	return 0;
}