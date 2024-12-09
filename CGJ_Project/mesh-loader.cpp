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

    //root->transform(glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    root->setAngle(90.0f);
    root->setCoordinates(startCoordsRoot);
    root->setRotationAxis(glm::vec3(1.0f, 0.0f, 0.0f));

    //child 0
    children.at(0)->setAngle(startAngle0);
    children.at(0)->setCoordinates(startCoords0);
    //children.at(0)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 1
    children.at(1)->setAngle(startAngle1);
    children.at(1)->setScale(2);
    children.at(1)->setCoordinates(startCoords1);
    //children.at(1)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 2
    children.at(2)->setScale(2.0f);
    children.at(2)->setAngle(startAngle2);
    children.at(2)->setCoordinates(startCoords2);
    //children.at(2)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 3
    children.at(3)->setAngle(startAngle3);
    children.at(3)->setCoordinates(startCoords3);
    //children.at(3)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 4
    children.at(4)->setScale(sqrt(2));
    children.at(4)->setAngle(startAngle4);
    children.at(4)->setCoordinates(startCoords4);
    //children.at(4)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 5
    children.at(5)->setAngle(startAngle5);
    children.at(5)->setCoordinates(startCoords5);
    //children.at(5)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));

    //child 6
    children.at(6)->setAngle(startAngle6);
    children.at(6)->setCoordinates(startCoords6);
    //children.at(6)->setRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f));
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

void MyApp::displayCallback(GLFWwindow *win, double elapsed) { drawScene(); }

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
    engine.setWindow(800, 600, "Mesh Loader", 0, 1);
    engine.init();
    engine.run();
    exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
