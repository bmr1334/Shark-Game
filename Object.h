//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 size;
	glm::mat4 worldTransform;
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	enum Colliders { noclip, aabb, sphere };
	Colliders collides = noclip;
};

class Object{
public:
	//variables
	std::string tag;
	std::string texFile;

	//initialize tag variable
	Object();
	
	//pure-virtual, no body
	virtual void Update();

	//prints tag variable to console
	void Render();

	//virtual destructor
	virtual ~Object();

	//collisions
	bool CollidesWith(Transform &loc1, Transform &loc2);
};