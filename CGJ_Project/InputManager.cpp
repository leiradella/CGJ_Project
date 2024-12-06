#include "InputManager.h"
#include <stdio.h>

bool InputManager::leftMouseButton = NOT_PRESSED;
double InputManager::cursorXPos = 0.0f;
double InputManager::cursorYPos = 0.0f;
double InputManager::startCursorXPos = 0.0f;
double InputManager::startCursorYPos = 0.0f;

InputManager::InputManager() {}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    //save mouse button state
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //if pressed, save the position
        leftMouseButton = PRESSED;
        glfwGetCursorPos(window, &startCursorXPos, &startCursorYPos);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMouseButton = NOT_PRESSED;

    }
}

void InputManager::cursorCallback(GLFWwindow* window, double xpos, double ypos) {

    if (leftMouseButton == PRESSED) {

        //calculate new cam coords
        //final formula will be something like this
        //camX = 2 * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
        //camZ = 2 * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
        //camY = 2 * sin(betaAux * 3.14f / 180.0f);
 
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(camX, camY, camY), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        printf(":D");
        camera->setViewMatrix(viewMatrix);
    }
}

void InputManager::setCamera(mgl::Camera* camera) {
    InputManager::camera = camera;
}
