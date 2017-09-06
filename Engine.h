//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#pragma once

#include "Timer.h"
#include "Model.h"
#include "Object.h"

class Engine{
public:
	//variables
	static Timer time;
	static GLFWwindow* GLFWwindowPtr;
	static std::vector<Object> objCollection;

	//start engine
	static void Start();

	//buffer models
	static bool bufferModels();

	//stop engine
	static void Stop();

	//update timer, clear console
	static void Update();
};