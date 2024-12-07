#include "InputManager.h"

Projection InputManager::projection = PERSPECTIVE;
bool InputManager::leftMouseButton = NOT_PRESSED;
double InputManager::cursorXPos = 0.0f;
double InputManager::cursorYPos = 0.0f;
double InputManager::startCursorXPos = 0.0f;
double InputManager::startCursorYPos = 0.0f;

InputManager::InputManager() { radius = 0.0f; rotY = 0.0f; rotX = 0.0f; }

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
    double deltaX, deltaY;
    float angle, deltaPitch, newPitch;
    glm::vec3 axis(0.0f); 
    glm::vec3 eye = camera->getEye();
    glm::vec3 center = camera->getCenter();
    glm::vec3 up = camera->getUp();

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
        rotX += deltaX * 0.01f;                // Horizontal rotation
        rotY += deltaY * 0.01f;              // Vertical rotation

        // Clamp rotY to avoid flipping at poles
        float epsilon = 0.01f; // Small buffer to avoid gimbal lock
        rotY = glm::clamp(rotY, -glm::half_pi<float>() + epsilon, glm::half_pi<float>() - epsilon);

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
        camera->setViewMatrix(eye, center, up);

        startCursorXPos = cursorXPos;
        startCursorYPos = cursorYPos;
    }
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

    glm::vec3 viewDir = glm::normalize(camera->getEye() - camera->getCenter());
    glm::vec3 eye = camera->getEye();
    glm::vec3 center = camera->getCenter();
    glm::vec3 up = camera->getUp();

    radius = glm::length(eye - center) + yoffset;
    rotX = glm::atan(viewDir.z, viewDir.x); // Angle in the XZ plane
    rotY = glm::asin(viewDir.y);          // Vertical angle

    viewDir.x = radius * glm::cos(rotY) * glm::cos(rotX);
    viewDir.y = radius * glm::sin(rotY);
    viewDir.z = radius * glm::cos(rotY) * glm::sin(rotX);

    // Update the eye position
    eye = center + viewDir;

    // Recompute the up vector
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), viewDir));
    up = glm::normalize(glm::cross(viewDir, right));


    //printf("x = %f, y = %f, z = %f\n", camCoords.x, camCoords.y, camCoords.z);
    camera->setViewMatrix(eye, center, up);
}

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
const glm::mat4 ProjectionMatrix1 =
glm::perspective(glm::radians(30.0f), 640.0f / 480.0f, 1.0f, 10.0f);

// Orthographic LeftRight(-2,2) BottomTop(-2,2) NearFar(1,10)
const glm::mat4 ProjectionMatrix2 =
glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        if (projection == PERSPECTIVE) {
            projection = ORTHOGONAL;
            camera->setProjectionMatrix(ProjectionMatrix2);
        }
        else {
            projection = PERSPECTIVE;
            camera->setProjectionMatrix(ProjectionMatrix1);
        }
    }
}

void InputManager::setCamera(mgl::Camera* camera) {
    InputManager::camera = camera;
    camera->setProjectionMatrix(ProjectionMatrix1);
    projection = PERSPECTIVE;

    camera->setViewMatrix(camera->getEye(), camera->getCenter(), camera->getUp());
}
