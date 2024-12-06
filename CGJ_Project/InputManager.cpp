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
        printf("%f\n", pitch);
        leftMouseButton = PRESSED;
        glfwGetCursorPos(window, &startCursorXPos, &startCursorYPos);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMouseButton = NOT_PRESSED;

    }
}

void InputManager::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    double deltaX, deltaY;
    float angle, deltaPitch, newPitch;
    glm::vec3 axis(0.0f), camCoords(0.0f);

    if (leftMouseButton == PRESSED) {

        //get the variation in cursor coordinates
        glfwGetCursorPos(window, &cursorXPos, &cursorYPos);
        deltaX = cursorXPos - startCursorXPos;
        deltaY = cursorYPos - startCursorYPos;

        //compute angle and axis
        angle = 0.01f * glm::length(glm::vec2(deltaX, deltaY));

        //if there was no variation in mouse coords, return
        if ((deltaX == 0) && (deltaY == 0)) {
            return;
        }

        axis = glm::normalize(glm::vec3(deltaY, -deltaX, 0.0f));


        glm::quat q = glm::angleAxis(angle, axis);
        glm::quat qInv = glm::inverse(q);

        camCoords = q * camCoords * qInv;
 
        glm::mat4 viewMatrix = glm::lookAt(camCoords, glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 eye = camCoords;
        glm::vec3 center = camera->getCenter();
        glm::vec3 up = camera->getUp();

        //printf("x = %f, y = %f, z = %f\n", camCoords.x, camCoords.y, camCoords.z);
        camera->setViewMatrix(eye, center, up);

        startCursorXPos = cursorXPos;
        startCursorYPos = cursorYPos;
    }
}

void InputManager::setCamera(mgl::Camera* camera) {
    InputManager::camera = camera;
}
