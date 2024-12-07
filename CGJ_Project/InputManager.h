#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "../mgl/mgl.hpp"

#define PRESSED true
#define NOT_PRESSED false

enum Projection
{
	PERSPECTIVE,
	ORTHOGONAL
};

class InputManager {
public:
	InputManager();

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	
	// reference to the camera
	mgl::Camera* camera = nullptr;
	void setCamera(mgl::Camera* camera);
private:
	static Projection projection;


	float radius;
	float rotX;
	float rotY;

	//key states, they can either be PRESSED or NOT_PRESSED
	//key states are saved between calls of the callback functions from GLFW
	static bool leftMouseButton;
	static double cursorXPos, cursorYPos;
	static double startCursorXPos, startCursorYPos;
};

