//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#pragma once

#include <ctime>

class Timer{
private:
	clock_t cur, prev;
public:
	//variables
	float timeSinceStart;
	float dt;	//delta time
	float fps;	//updates per second

	//initializes time variables
	Timer();

	//updates time variables
	void Update();

	//destructor
	~Timer();
};