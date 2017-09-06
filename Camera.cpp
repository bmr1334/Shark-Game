//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Camera.h"

using namespace glm;

//used to update camera location
vec3 camDirection;

//constructor does nothing
Camera::Camera(){
}

//updates and uploads camera data
vec3 Camera::updateCamera(float & dt){
	//calculate camera look-at matrix and rotation matrix
	camViewpoint = camLocation;
	rotationMat = (mat3)yawPitchRoll(trans.rotation.y, trans.rotation.x, trans.rotation.z);
	vec3 camViewpoint = camLocation;
	vec3 center = camViewpoint + rotationMat * vec3(0, 0, -1);
	vec3 up = rotationMat * vec3(0, 1, 0);
	lookatMat = lookAt(camViewpoint, center, up);

	//calculate camera matrix data
	worldViewMat = perspectiveMat * lookatMat;

	//physics movement -- drag and gravity
	float cDrag = -5;
	trans.force += cDrag * trans.velocity;
	trans.mass = 5;

	//update camera viewpoint and camera location
	trans.velocity += (trans.force / trans.mass) * dt ;
	camLocation += trans.velocity * dt;
	camViewpoint = camLocation;

	//upload camera matrix data
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldViewMat[0][0]);
	glUniform3f(3, camLocation.x, camLocation.y, camLocation.z); //camera data

	return center;
}

//allows FPS-style movement
void Camera::fpsMovement(GLFWwindow * window, float & dt){
	//variables
	float mouseSensitivity = .005f;
	double cursorX, cursorY;
	
	//get cursor location values
	glfwGetCursorPos(window, &cursorX, &cursorY);
	glfwGetWindowSize(window, &width, &height);

	//calculate camera rotation
	trans.rotation.y -= mouseSensitivity * (cursorX - width * 0.5f); //yaw
	trans.rotation.x -= mouseSensitivity * (cursorY - height * 0.5f); //pitch
	trans.rotation.x = clamp(trans.rotation.x, -0.5f * 3.1415926f, 0.5f * 3.1415926f);
	glfwSetCursorPos(window, width * 0.5f, height * 0.5f);

	//move forward
	if (glfwGetKey(window, GLFW_KEY_W)) {
		camDirection.z -= 1;
	}
	
	//set movement speed
	float moveSpeed = 3.0f;

	//normalizes speed to prevent ultrafast movement
	if (camDirection != vec3())
		camDirection = normalize(camDirection);

	//set camera velocity
	trans.force = rotationMat * camDirection * moveSpeed;
}

Camera::~Camera(){
}