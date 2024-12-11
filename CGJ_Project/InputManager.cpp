#include "InputManager.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

bool InputManager::rightArrow = NOT_PRESSED;
bool InputManager::leftArrow = NOT_PRESSED;
bool InputManager::leftMouseButton = NOT_PRESSED;
double InputManager::cursorXPos = 0.0f;
double InputManager::cursorYPos = 0.0f;
double InputManager::startCursorXPos = 0.0f;
double InputManager::startCursorYPos = 0.0f;

InputManager::InputManager() { radius = 0.0f; rotY = 0.0f; rotX = 0.0f; UBO_BP = 5; }

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    //save mouse button state
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            //if pressed, save the position
            leftMouseButton = PRESSED;
            glfwGetCursorPos(window, &startCursorXPos, &startCursorYPos);
        }
        else if (action == GLFW_RELEASE) {
            leftMouseButton = NOT_PRESSED;
        }
    }
}

void InputManager::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    double deltaX, deltaY;
    glm::vec3 axis(0.0f); 
    glm::vec3 eye = activeCamera->getEye();
    glm::vec3 center = activeCamera->getCenter();
    glm::vec3 up = activeCamera->getUp();

    if (leftMouseButton == PRESSED) {

        //get the variation in cursor coordinates
        glfwGetCursorPos(window, &cursorXPos, &cursorYPos);
        deltaX = cursorXPos - startCursorXPos;
        deltaY = cursorYPos - startCursorYPos;

        // Compute the spherical coordinates
        glm::vec3 viewDir = glm::normalize(eye - center);

        // Calculate rotX and rotY from the current view direction
        radius = glm::length(eye - center);
        rotX = glm::atan(viewDir.z, viewDir.x); // Angle in the XZ plane
        rotY = glm::asin(viewDir.y);          // Vertical angle

        // Update angles based on input deltas
        rotX += (float)(deltaX) * 0.01f;
        rotY += (float)(deltaY) * 0.01f;

        // Clamp rotY to avoid flipping at poles
        float epsilon = 0.01f; // Small buffer to avoid gimbal lock
        rotY = glm::clamp(rotY, -glm::pi<float>()/2 + epsilon, glm::pi<float>()/2 - epsilon);

        // Convert spherical coordinates back to Cartesian coordinates
        viewDir.x = radius * glm::cos(rotY) * glm::cos(rotX);
        viewDir.y = radius * glm::sin(rotY);
        viewDir.z = radius * glm::cos(rotY) * glm::sin(rotX);

        // Update the eye position
        eye = center + viewDir;

        // Recompute the up vector
        glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), viewDir));
        up = glm::normalize(glm::cross(viewDir, right));
        

        //printf("x = %f, y = %f, z = %f\n", camCoords.x, camCoords.y, camCoords.z);
        activeCamera->setViewMatrix(eye, center, up);

        startCursorXPos = cursorXPos;
        startCursorYPos = cursorYPos;
    }
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

    glm::vec3 viewDir = glm::normalize(activeCamera->getEye() - activeCamera->getCenter());
    glm::vec3 eye = activeCamera->getEye();
    glm::vec3 center = activeCamera->getCenter();
    glm::vec3 up = activeCamera->getUp();

    radius = glm::length(eye - center) - (float)(yoffset);
    rotX = (float)(glm::atan(viewDir.z, viewDir.x));
    rotY = glm::asin(viewDir.y);

    if (radius < 3.0f) {
        radius = 3.0f;
        return;
    }

    viewDir.x = radius * glm::cos(rotY) * glm::cos(rotX);
    viewDir.y = radius * glm::sin(rotY);
    viewDir.z = radius * glm::cos(rotY) * glm::sin(rotX);

    // Update the eye position
    eye = center + viewDir;

    // Recompute the up vector
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), viewDir));
    up = glm::normalize(glm::cross(viewDir, right));


    //printf("x = %f, y = %f, z = %f\n", camCoords.x, camCoords.y, camCoords.z);
    activeCamera->setViewMatrix(eye, center, up);
}

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
static glm::mat4 perspectiveProjection =
glm::perspective(glm::radians(30.0f), 1.0f, 1.0f, 1000.0f);

// Orthographic LeftRight(-2,2) BottomTop(-2,2) NearFar(1,10)
static glm::mat4 orthogonalProjection =
glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, 1.0f, 1000.0f);

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_P:
        if (action == GLFW_PRESS) {
            swapProjectionMatrix();
        }
        break;
    case GLFW_KEY_C:
        if (action == GLFW_PRESS) {
            if (activeCamera == camera1) {
                setActiveCamera(camera2);
            }
            else if (activeCamera == camera2) {
                setActiveCamera(camera1);
            }
        }
        break;
    case GLFW_KEY_LEFT:
        if (action == GLFW_RELEASE) {
            leftArrow = NOT_PRESSED;
        }
        else if (action == GLFW_PRESS || leftArrow == PRESSED) {
            leftArrow = PRESSED;
        }
        break;
    case GLFW_KEY_RIGHT:
        if (action == GLFW_RELEASE) {
            rightArrow = NOT_PRESSED;
        }
        else if (action == GLFW_PRESS || rightArrow == PRESSED) {
            rightArrow = PRESSED;
        }
        break;
    default:
        if (action == GLFW_PRESS){
            printf("unrecognised key\n");
        }
        break;
    }
}

void InputManager::windowSizeCallback(GLFWwindow* window, int width, int height) {
    float ratio;
    //avoid division by 0
    if (height == 0) { height = 1; }
    glViewport(0, 0, width, height);
    ratio = (1.0f * width) / height;
    const glm::mat4 newPerspectiveProjection = glm::perspective(glm::radians(30.0f), ratio, 1.0f, 1000.0f);
    const glm::mat4 newOrthogonalProjection = glm::ortho(-width / 200.0f, width / 200.0f, -height / 200.0f, height / 200.0f, 1.0f, 1000.0f);
    if (activeCamera->getProjectionMatrix() == perspectiveProjection) {
        activeCamera->setProjectionMatrix(newPerspectiveProjection);
    }
    else {
        activeCamera->setProjectionMatrix(newOrthogonalProjection);
    }
    orthogonalProjection = newOrthogonalProjection;
    perspectiveProjection = newPerspectiveProjection;
}

void InputManager::setCamera(mgl::Camera* camera) {

    camera->setProjectionMatrix(perspectiveProjection);
    if (camera1 == nullptr) {
        camera1 = camera;
        camera1->setViewMatrix(glm::vec3(3.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            camera1->getUp());
    }
    else if (camera2 == nullptr) {
        camera2 = camera;
        camera2->setViewMatrix(glm::vec3(5.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            camera2->getUp());
    }
    else {
        printf("InputManager: tried to set too many cameras (limit = 2)\n");
    }
}
bool InputManager::isLeftArowPresed() {
    return leftArrow;
}

bool InputManager::isRightArowPresed() {
    return rightArrow;
}

void InputManager::setActiveCamera(mgl::Camera* camera) {
    activeCamera = camera;
    
    glGenBuffers(1, &activeCamera->UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, activeCamera->UboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, 0, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, activeCamera->UboId);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    activeCamera->setProjectionMatrix(activeCamera->getProjectionMatrix());
    activeCamera->setViewMatrix(activeCamera->getEye(), activeCamera->getCenter(), activeCamera->getUp());
}

void InputManager::setUBO(GLuint UBO) {
    UBO_BP = UBO;
}

void InputManager::setRootNode(SceneNode* root) {
    this->root = root;
}

void InputManager::swapProjectionMatrix() {
    if (activeCamera->getProjectionMatrix() == perspectiveProjection) {
        activeCamera->setProjectionMatrix(orthogonalProjection);
    }
    else {
        activeCamera->setProjectionMatrix(perspectiveProjection);
    }
}
