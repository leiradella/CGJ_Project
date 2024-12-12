////////////////////////////////////////////////////////////////////////////////
//
//  Loading meshes from external files
//
// Copyright (c) 2023-24 by Carlos Martinho
//
// INTRODUCES:
// MODEL DATA, ASSIMP, mglMesh.hpp
//
////////////////////////////////////////////////////////////////////////////////
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../mgl/mgl.hpp"
#include <iostream>

#include "InputManager.h"
#include "scene-graph.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
    void initCallback(GLFWwindow *win) override;
    void displayCallback(GLFWwindow *win, double elapsed) override;
    void windowSizeCallback(GLFWwindow *win, int width, int height) override;
    void mouseButtonCallback(GLFWwindow* window, int button, int action,
      int mods) override;
    void cursorCallback(GLFWwindow* window, double xpos, double ypos) override;
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;


 private:
     const GLuint UBO_BP = 0;
    mgl::ShaderProgram *Shaders = nullptr;
    mgl::Camera* Camera1 = nullptr;
    mgl::Camera* Camera2 = nullptr;
    GLint ModelMatrixId = 0;
    glm::mat4 ModelMatrix = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //glm::identity<glm::mat4>();
  
    SceneNode* root = nullptr;
    InputManager *inputManager = nullptr;
    GLint BaseColorId = 0;
    mgl::Mesh* createMesh(std::string meshFile);
    void createShaderPrograms();
    void createSceneGraph();
    void createCamera();
    void createInputManager();
    void drawScene();
    void playAnimation(double deltaT);
};

///////////////////////////////////////////////////////////////////////// MESHES

mgl::Mesh* MyApp::createMesh(std::string meshFile) {
  std::string mesh_dir = "../assets/";
  std::string mesh_fullname = mesh_dir + meshFile;


  mgl::Mesh* mesh = new mgl::Mesh();
  mesh->joinIdenticalVertices();
  mesh->create(mesh_fullname);
  return mesh;
}

///////////////////////////////////////////////////////////////////////// SHADER

void MyApp::createShaderPrograms() {
  Shaders = new mgl::ShaderProgram();
  Shaders->addShader(GL_VERTEX_SHADER, "cube-vs.glsl");
  Shaders->addShader(GL_FRAGMENT_SHADER, "cube-fs.glsl");

  Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);
  Shaders->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);

  Shaders->addUniform("BaseColor");
  Shaders->addUniform(mgl::MODEL_MATRIX);
  Shaders->addUniformBlock(mgl::CAMERA_BLOCK, UBO_BP);
  Shaders->create();

  BaseColorId = Shaders->Uniforms["BaseColor"].index;
  ModelMatrixId = Shaders->Uniforms[mgl::MODEL_MATRIX].index;
}

///////////////////////////////////////////////////////////////////////// SCENE GRAPH

void MyApp::createSceneGraph() {
    mgl::Mesh* triangleMesh = createMesh("Triangle_piece_vn.obj");
    mgl::Mesh* squareMesh = createMesh("Square_piece_vn.obj");
    mgl::Mesh* parallelogramMesh = createMesh("Parallelogram_piece_vn.obj");

    root = new SceneNode(nullptr, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Shaders);

    root->addChild(new SceneNode(triangleMesh, glm::vec4(0.9254901961f, 0.1098039216f, 0.1411764706f, 1.0f), Shaders));
    root->addChild(new SceneNode(triangleMesh, glm::vec4(0.2745098039f, 0.5882352941f, 0.9294117647f, 1.0f), Shaders));
    root->addChild(new SceneNode(triangleMesh, glm::vec4(0.4431372549f, 0.7490196078f, 0.2705882353f, 1.0f), Shaders));
    root->addChild(new SceneNode(triangleMesh, glm::vec4(0.8274509804f, 0.831372549f, 0.8392156863f, 1.0f), Shaders));
    root->addChild(new SceneNode(triangleMesh, glm::vec4(0.9568627451f, 0.5137254902f, 0.1215686275f, 1.0f), Shaders));
    root->addChild(new SceneNode(squareMesh, glm::vec4(1.0f, 0.7607843137f, 0.05882352941f, 1.0f), Shaders));
    root->addChild(new SceneNode(parallelogramMesh, glm::vec4(0.6862745098f, 0.5960784314f, 0.8274509804f, 1.0f), Shaders));

    std::vector<SceneNode*> children = root->getChildren();

    //child 0
    children.at(0)->setMatrix(glm::translate(startCoords0) * glm::rotate(glm::radians(startAngle0), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 1
    children.at(1)->setScale(2.0f);
    children.at(1)->setMatrix(glm::translate(startCoords1) * glm::rotate(glm::radians(startAngle1), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 2
    children.at(2)->setScale(2.0f);
    children.at(2)->setMatrix(glm::translate(startCoords2) * glm::rotate(glm::radians(startAngle2), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 3
    children.at(3)->setMatrix(glm::translate(startCoords3) * glm::rotate(glm::radians(startAngle3), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 4
    children.at(4)->setScale(sqrt(2));
    children.at(4)->setMatrix(glm::translate(startCoords4) * glm::rotate(glm::radians(startAngle4), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 5
    children.at(5)->setMatrix(glm::translate(startCoords5) * glm::rotate(glm::radians(startAngle5), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 6
    children.at(6)->setMatrix(glm::translate(startCoords6) * glm::rotate(glm::radians(startAngle6), glm::vec3(0.0f, 0.0f, 1.0f)));
}

///////////////////////////////////////////////////////////////////////// CAMERA

void MyApp::createCamera() {
    Camera1 = new mgl::Camera(UBO_BP);
    Camera2 = new mgl::Camera(1);
    //glm::vec3 eye(5.0f, 5.0f, 5.0f);
    //glm::vec3 center(0.0f, 0.0f, 0.0f); 
    //glm::vec3 up(0.0f, 1.0f, 0.0f);
    //Camera->setViewMatrix(eye, center, up);
    //Camera->setProjectionMatrix(ProjectionMatrix2);
}

/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::drawScene() {
    std::vector<SceneNode*> children = root->getChildren();
    root->draw(ModelMatrixId, BaseColorId);
    //for (int i = 0; i < children.size(); i++) {
    //    children.at(i)->draw(ModelMatrixId, BaseColorId);
    //}
}

void MyApp::playAnimation(double deltaT) {
    std::vector<SceneNode*> children = root->getChildren();

    //node parameters
    glm::vec3 coords(0.0f);
    glm::vec3 rotAxis(0.0f);
    float angle = 0;
    float scale = 0;

    //interpolation variables
    static float t = 0.0f;
    float step = deltaT;

    //INTERPOLATION FORMULA: START (A) -> END (B), T[0,1]
    // VALUE = (B - A)*T + A
    // WHEN T = 0, VALUE = A
    // WHEN T = 1, VALUE = B


    //child 0 red triangle
    coords = (endCoords0 - startCoords0) * t + startCoords0;
    angle = (endAngle0 - startAngle0) * t + startAngle0;
    children.at(0)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 1 blue triangle
    coords = (endCoords1 - startCoords1) * t + startCoords1;
    angle = (endAngle1 - startAngle1) * t + startAngle1;
    children.at(1)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 2 green triangle
    coords = (endCoords2 - startCoords2) * t + startCoords2;
    angle = (endAngle2 - startAngle2) * t + startAngle2;
    children.at(2)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 3 white triangle
    coords = (endCoords3 - startCoords3) * t + startCoords3;
    angle = (endAngle3 - startAngle3) * t + startAngle3;
    children.at(3)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 4 oreange triangle
    coords = (endCoords4 - startCoords4) * t + startCoords4;
    angle = (endAngle4 - startAngle4) * t + startAngle4;
    children.at(4)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 5 yellow square
    coords = (endCoords5 - startCoords5) * t + startCoords5;
    angle = (endAngle5 - startAngle5) * t + startAngle5;
    children.at(5)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //child 6 purple parallelogram
    coords = (endCoords6 - startCoords6) * t + startCoords6;
    angle = (endAngle6 - startAngle6) * t + startAngle6;
    children.at(6)->setMatrix(glm::translate(coords) * glm::rotate(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));

    //root
    angle = (endAngleRoot - startAngleRoot) * t + startAngleRoot;
    root->setMatrix(glm::rotate(glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)));

    if (inputManager->isRightArowPresed() && t < 1.0f) {
        t += step;
    }
    else if (inputManager->isLeftArowPresed() && t > 0.0f) {
        t -= step;
    }

    if (t > 1.0f) {
        t = 1.0f;
    }
    else if (t < 0.0f) {
        t = 0.0f;
    }
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    createShaderPrograms();  // after mesh;
    createSceneGraph();
    createCamera();
    createInputManager();
}

void MyApp::windowSizeCallback(GLFWwindow *win, int width, int height) {
    inputManager->windowSizeCallback(win, width, height);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    if (inputManager->isLeftArowPresed() || inputManager->isRightArowPresed()) {
        playAnimation(elapsed);
    }
    drawScene();
}

void MyApp::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    inputManager->mouseButtonCallback(window, button, action, mods);
}

void MyApp::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    inputManager->cursorCallback(window, xpos, ypos);
}

void MyApp::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    inputManager->keyCallback(window, key, scancode, action, mods);
}

void MyApp::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    inputManager->scrollCallback(window, xoffset, yoffset);
}

/////////////////////////////////////////////////////////////////////////// INPUT MANAGER

void MyApp::createInputManager() {
    inputManager = new InputManager;
    inputManager->setUBO(UBO_BP);
    inputManager->setRootNode(root);
    inputManager->setCamera(Camera1);
    inputManager->setCamera(Camera2);
    inputManager->setActiveCamera(Camera1);
}

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
    mgl::Engine &engine = mgl::Engine::getInstance();
    engine.setApp(new MyApp());
    engine.setOpenGL(4, 6);
    engine.setWindow(800, 800, "Mesh Loader", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
