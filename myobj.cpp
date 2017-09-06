//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <iostream>

#include "Engine.h"
#include "myobj.h"

//initializes tag variable
myobj::myobj(){
	tag = "myobjtag";
}

//update override to print time to the console
void myobj::Update(){
	std::cout << "Updating at time: " << Engine::time.timeSinceStart << std::endl;
}

//override destructor
myobj::~myobj() {
}