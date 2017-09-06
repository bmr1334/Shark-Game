//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <iostream>

#include "Object.h"

//initialize tag variable
Object::Object(){
	tag = "";
}

//pure-virtual, no body
void Object::Update(){
}

//prints tag variable to console
void Object::Render(){
	std::cout << "Rendering [" << tag << "]" << std::endl;
}

bool Object::CollidesWith(Transform &loc1, Transform &loc2)
{
	//if they are both noclip, they can never collide
	if (loc1.collides == loc1.noclip && loc2.collides == loc2.noclip) {
		return false;
	}

	//if they're both sphere colliders
	if (loc1.collides == loc1.sphere && loc2.collides == loc2.sphere) {

		//are they overlapping?
		float distance = pow((loc1.location.z - loc2.location.z), 2) + pow((loc1.location.x - loc2.location.x), 2) + pow((loc1.location.y - loc2.location.y), 2);
		distance = sqrt(distance);
		if (distance > loc1.size.x + loc2.size.x) {
			return false;
		}
	}

	//if they're both aabb colliders
	if (loc1.collides == loc1.aabb && loc2.collides == loc2.aabb) {
		bool xColl = false;
		bool yColl = false;
		bool zColl = false;

		//colliding on x axis?
		if (loc2.location.x - loc2.size.x < loc1.location.x + loc1.size.x || loc2.location.x + loc2.size.x > loc1.location.x - loc1.size.x) {
			xColl = true;
		}

		//colliding on y axis?
		if (loc2.location.y - loc2.size.y < loc1.location.y + loc1.size.y || loc2.location.y + loc2.size.y > loc1.location.y - loc1.size.y) {
			yColl = true;
		}

		//colliding on z axis?
		if (loc2.location.z - loc2.size.z < loc1.location.z + loc1.size.z || loc2.location.z + loc2.size.z > loc1.location.z - loc1.size.z) {
			zColl = true;
		}

		//if above 3 checks pass
		if (xColl == false && yColl == false && zColl == false) {
			return false;
		}
	}

	//if one is aabb and the other is sphere
	if (loc1.collides == loc1.aabb && loc2.collides == loc2.sphere) {
		float distance = 0.0f;
		glm::vec3 p;

		p = loc1.location + glm::clamp(loc2.location - loc1.location, -loc1.size, loc1.size);

		glm::vec3 dp = loc2.location - p;
		float squareDistance = pow(dp.x, 2) + pow(dp.y, 2) + pow(dp.z, 2);
		if (squareDistance > pow(loc2.size.x,2)) {
			return false;
		}
	}

	//returns true if none of the above succeed
	return true;
}

//virtual destructor
Object::~Object() {
}