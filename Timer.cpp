//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include "Timer.h"

//initializes time variables
Timer::Timer(){
	prev = cur = clock();
	timeSinceStart = dt = fps = 0;
}

//updates time variables
void Timer::Update(){
	prev = cur;
	cur = clock();
	dt = (cur - prev) / (float)CLOCKS_PER_SEC;
	timeSinceStart += dt;
	fps = 1 / dt;
}

//destructor
Timer::~Timer() {
}