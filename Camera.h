//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#pragma once

#include <FreeImage.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Object.h"

using namespace glm;

class Camera : Object{
private:
	//general variables
	mat4 worldViewMat = mat4();
	vec3 velocity;
	Transform trans = Transform();

	//perspective matrix variables
	float zoom = 1.0f;
	int width = 1920;
	int height = 1080;
	float fovy = 0.4f * 3.1415926f / zoom;
	float aspectRatio = (float)width / (float)height;
	float zNear = 0.001f;
	float zFar = 1000.0f;
	mat4 perspectiveMat = perspective(fovy, aspectRatio, zNear, zFar);

	//look-at matrix variables
	vec3 camLocation = { 0,0,1 };
	vec3 camRotation = { 0,0,0 };
	mat3 rotationMat = (mat3)yawPitchRoll(trans.rotation.y, trans.rotation.x, trans.rotation.z);
	vec3 camViewpoint = camLocation;
	vec3 center = camViewpoint + rotationMat * vec3(0, 0, -1);
	vec3 up = rotationMat * vec3(0, 1, 0);
	mat4 lookatMat = lookAt(camViewpoint, center, up);

public:
	//constructor does nothing
	Camera();

	//updates and uploads camera data
	vec3 updateCamera(float &dt);

	//allows for FPS-style movement
	void fpsMovement(GLFWwindow * window, float &dt);

	//always make sure destructor is virtual to prevent memory leaks
	virtual ~Camera();
};