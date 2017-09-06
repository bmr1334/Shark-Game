//include formatting order: basic externals, GL, glm, headers, namespaces
//Brandon M. Rodriguez

#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Engine.h"
#include "Timer.h"
#include "Shader.h"
#include "Camera.h"

Timer Engine::time;
GLFWwindow* Engine::GLFWwindowPtr;
bool meat1Pickup = false;
bool meat2Pickup = false;
bool meat3Pickup = false;
bool meat4Pickup = false;
bool meat5Pickup = false;

//used to load in/do model computations
Object obj = Object(); //used for collision detection
Camera cam = Camera();
Model rock1 = Model(); //rock models
Model rock2 = Model();
Model rock3 = Model();
Model sand1 = Model(); //sand planes
Model camColl = Model(); //collider around camera
Model meat1 = Model(); //collectible meat objects
Model meat2 = Model();
Model meat3 = Model();
Model meat4 = Model();
Model meat5 = Model();
vec3 camCenter;

//start engine
void Engine::Start(){
	//variables
	Shader shade = Shader(); //instance of Shader class
	
	//initialize the window library
	if (glfwInit() == GL_FALSE) {
	}

	//create a windowed mode window
	GLFWwindowPtr = glfwCreateWindow(1920, 1080, "Rodriguez DSA1 - Infinium Engine", glfwGetPrimaryMonitor(), NULL);

	//and make it the currently active window, or quit
	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
	}

	//initialize GLEW, or quit
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
	}

	//enable wireframe -- only use for debugging!
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//define window color
	glClearColor(0.f, 0.f, 0.3f, 0.0f);

	//load shader
	bool loadingCheck = shade.load();

	//if shader loading succeeded, use the shader
	if (loadingCheck) {
		shade.use();
	}

	//enable transparency/alpha layer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//enable backface culling -- very important for performance
	glEnable(GL_CULL_FACE);

	//hide cursor
	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//create depth buffer
	glEnable(GL_DEPTH_TEST);

	//light in scene
	glUniform3f(5, 3.0f, 10.0f, 5.0f); //light data
}

//buffer in models
bool Engine::bufferModels()
{	
	rock1.Texture("Textures/Rock_6_d.png");
	rock1.Buffer("Models/Rock_6.obj");
	
	rock2.Texture("Textures/SandTex.tif");
	rock2.Buffer("Models/Rock_6.obj");
	
	sand1.Texture("Textures/Rock_6_d.png");
	sand1.trans.collides = Transform::Colliders::aabb;
	sand1.Buffer("Models/quad.obj");

	rock3.Texture("Textures/Meat_texture.jpg");
	rock3.Buffer("Models/Rock_6.obj");

	camColl.Texture("Textures/Rock_6_d.png");
	camColl.trans.collides = Transform::Colliders::sphere;
	camColl.Buffer("Models/sphere.obj");

	//meat that can be picked up
	meat1.Texture("Textures/Meat_texture.jpg");
	meat1.trans.collides = Transform::Colliders::sphere;
	meat1.Buffer("Models/meat.obj");

	meat2.Texture("Textures/Meat_texture.jpg");
	meat2.trans.collides = Transform::Colliders::sphere;
	meat2.Buffer("Models/meat.obj");

	meat3.Texture("Textures/Meat_texture.jpg");
	meat3.trans.collides = Transform::Colliders::sphere;
	meat3.Buffer("Models/meat.obj");

	meat4.Texture("Textures/Meat_texture.jpg");
	meat4.trans.collides = Transform::Colliders::sphere;
	meat4.Buffer("Models/meat.obj");

	meat5.Texture("Textures/Meat_texture.jpg");
	meat5.trans.collides = Transform::Colliders::sphere;
	meat5.Buffer("Models/meat.obj");

	return true;
}

//stop engine
void Engine::Stop(){

	//delete textures when finished with them
	glDeleteTextures(1, &rock1.texID);
	glDeleteTextures(1, &rock2.texID);
	glDeleteTextures(1, &rock3.texID);
	glDeleteTextures(1, &sand1.texID);
	glDeleteTextures(1, &camColl.texID);
	glDeleteTextures(1, &meat1.texID);
	glDeleteTextures(1, &meat2.texID);
	glDeleteTextures(1, &meat3.texID);
	glDeleteTextures(1, &meat4.texID);
	glDeleteTextures(1, &meat5.texID);

	//end program
	glfwInit();
	glfwTerminate();
}

//update timer, clear console
void Engine::Update(){
	time.Update();

	//clear the canvas/reset buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//update object transform data -- rock
	rock1.trans.size = { .5,.5,.5 };
	rock1.trans.location = { 1,-1,5 };
	glm::mat4 scaleMat = glm::scale(rock1.trans.size);
	glm::mat4 rotateMat = glm::yawPitchRoll(rock1.trans.rotation.y, rock1.trans.rotation.x, rock1.trans.rotation.z);
	glm::mat4 moveMat = glm::translate(rock1.trans.location);
	rock1.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &rock1.trans.worldTransform[0][0]);
	rock1.Render();

	//update object transform data -- rock
	rock2.trans.size = { .65,.65,.65 };
	rock2.trans.location = { 0,-1,-4 };
	scaleMat = glm::scale(rock2.trans.size);
	rotateMat = glm::yawPitchRoll(rock2.trans.rotation.y, rock2.trans.rotation.x, rock2.trans.rotation.z);
	moveMat = glm::translate(rock2.trans.location);
	rock2.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &rock2.trans.worldTransform[0][0]);
	rock2.Render();

	//update object transform data -- sand
	sand1.trans.size = { 10,10,10 };
	sand1.trans.location = { 0,-1,0 };
	sand1.trans.rotation = { 3.14159 / 2,0,0};
	scaleMat = glm::scale(sand1.trans.size);
	rotateMat = glm::yawPitchRoll(sand1.trans.rotation.y, sand1.trans.rotation.x, sand1.trans.rotation.z);
	moveMat = glm::translate(sand1.trans.location);
	sand1.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &sand1.trans.worldTransform[0][0]);
	sand1.Render();

	//update object transform data -- rock
	rock3.trans.size = { .75,.4,.75 };
	rock3.trans.location = { 3,-1.25,2 };
	rock3.trans.rotation = { 0,1,0 };
	scaleMat = glm::scale(rock3.trans.size);
	rotateMat = glm::yawPitchRoll(rock3.trans.rotation.y, rock3.trans.rotation.x, rock3.trans.rotation.z);
	moveMat = glm::translate(rock3.trans.location);
	rock3.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &rock3.trans.worldTransform[0][0]);
	rock3.Render();

	//update object transform data -- meat
	meat1.trans.size = { .05,.05,.05 };
	meat1.trans.location = { 3,0.5,-3 };
	meat1.trans.rotation = { 3.14159 / 2,0,0 };
	scaleMat = glm::scale(meat1.trans.size);
	rotateMat = glm::yawPitchRoll(meat1.trans.rotation.y, meat1.trans.rotation.x, meat1.trans.rotation.z);
	moveMat = glm::translate(meat1.trans.location);
	meat1.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &meat1.trans.worldTransform[0][0]);

	//only render meat when not touched by camera
	if (meat1Pickup == false) {
		meat1.Render();
	}

	//update object transform data -- meat
	meat2.trans.size = { .05,.05,.05 };
	meat2.trans.location = { 1,0.3,-2 };
	meat2.trans.rotation = { 3.14159 / 2,0,0 };
	scaleMat = glm::scale(meat2.trans.size);
	rotateMat = glm::yawPitchRoll(meat2.trans.rotation.y, meat2.trans.rotation.x, meat2.trans.rotation.z);
	moveMat = glm::translate(meat2.trans.location);
	meat2.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &meat2.trans.worldTransform[0][0]);

	//only render meat when not touched by camera
	if (meat2Pickup == false) {
		meat2.Render();
	}

	//update object transform data -- meat
	meat3.trans.size = { .05,.05,.05 };
	meat3.trans.location = { -1,0,2 };
	meat3.trans.rotation = { 3.14159 / 2,0,0 };
	scaleMat = glm::scale(meat3.trans.size);
	rotateMat = glm::yawPitchRoll(meat3.trans.rotation.y, meat3.trans.rotation.x, meat3.trans.rotation.z);
	moveMat = glm::translate(meat3.trans.location);
	meat3.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &meat3.trans.worldTransform[0][0]);

	//only render meat when not touched by camera
	if (meat3Pickup == false) {
		meat3.Render();
	}

	//update object transform data -- meat
	meat4.trans.size = { .05,.05,.05 };
	meat4.trans.location = { -1,-0.4,-2 };
	meat4.trans.rotation = { 3.14159 / 2,0,0 };
	scaleMat = glm::scale(meat4.trans.size);
	rotateMat = glm::yawPitchRoll(meat4.trans.rotation.y, meat4.trans.rotation.x, meat4.trans.rotation.z);
	moveMat = glm::translate(meat4.trans.location);
	meat4.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &meat4.trans.worldTransform[0][0]);

	//only render meat when not touched by camera
	if (meat4Pickup == false) {
		meat4.Render();
	}

	//update object transform data -- meat
	meat5.trans.size = { .05,.05,.05 };
	meat5.trans.location = { 1,-0.1,3 };
	meat5.trans.rotation = { 3.14159 / 2,0,0 };
	scaleMat = glm::scale(meat5.trans.size);
	rotateMat = glm::yawPitchRoll(meat5.trans.rotation.y, meat5.trans.rotation.x, meat5.trans.rotation.z);
	moveMat = glm::translate(meat5.trans.location);
	meat5.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &meat5.trans.worldTransform[0][0]);

	//only render meat when not touched by camera
	if (meat5Pickup == false) {
		meat5.Render();
	}
	
	//swap the front (what the screen displays) and back (what OpenGL draws to) buffers
	glfwSwapBuffers(GLFWwindowPtr);

	//process queued window, mouse & keyboard callback events
	glfwPollEvents();

	//call camera functions
	cam.fpsMovement(GLFWwindowPtr, time.dt);
	vec3 camCenter = cam.updateCamera(time.dt);

	//camera collider -- HAS to be after "call camera functions" to work properly
	camColl.trans.size = { .25,.25,.25 };
	camColl.trans.location = camCenter;
	scaleMat = glm::scale(camColl.trans.size);
	rotateMat = glm::yawPitchRoll(camColl.trans.rotation.y, camColl.trans.rotation.x, camColl.trans.rotation.z);
	moveMat = glm::translate(camColl.trans.location);
	camColl.trans.worldTransform = moveMat * rotateMat * scaleMat;

	//upload transform matrix data 
	glUniformMatrix4fv(6, 1, GL_FALSE, &camColl.trans.worldTransform[0][0]);
	camColl.Render();

	//collision checks -- camera vs the meats
	if (obj.CollidesWith(camColl.trans, meat1.trans)) {
		meat1Pickup = true;
	}
	if (obj.CollidesWith(camColl.trans, meat2.trans)) {
		meat2Pickup = true;
	}
	if (obj.CollidesWith(camColl.trans, meat3.trans)) {
		meat3Pickup = true;
	}
	if (obj.CollidesWith(camColl.trans, meat4.trans)) {
		meat4Pickup = true;
	}
	if (obj.CollidesWith(camColl.trans, meat5.trans)) {
		meat5Pickup = true;
	}
}