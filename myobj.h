//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#pragma once

#include "Object.h"

class myobj : public Object{
public:
	//initializes tag variable
	myobj();
	
	//update override to print time to the console
	void Update() override;

	//override destructor
	~myobj() override;
};

