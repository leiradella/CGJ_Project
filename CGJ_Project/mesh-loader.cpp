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

#include "../mgl/mgl.hpp"

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
    GLint ModelMatrixId;
  
    SceneNode* root = nullptr;
    InputManager *inputManager = nullptr;
    GLint BaseColorId;
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

    root->transform(glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

    children.at(0)->transform(glm::translate(glm::vec3(-sqrt(2), -2 * sqrt(2), 0.0f)) *
                              glm::rotate(glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    children.at(1)->transform(glm::translate(glm::vec3(0.0f, 2 * sqrt(2), 0.0f)) *
                              glm::rotate(glm::radians(315.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::scale(glm::vec3(2.0f, 2.0f, 1.0f)));
    children.at(2)->transform(glm::translate(glm::vec3(-2 * sqrt(2), 0.0f, 0.0f)) *
                              glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::scale(glm::vec3(2.0f, 2.0f, 1.0f)));
    children.at(3)->transform(glm::translate(glm::vec3(sqrt(2), 0.0f, 0.0f)) *
                              glm::rotate(glm::radians(225.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    children.at(4)->transform(glm::translate(glm::vec3(sqrt(2), -sqrt(2), 0.0f)) *
                              glm::scale(glm::vec3(sqrt(2), sqrt(2), 1.0f)));
    children.at(5)->transform(glm::translate(glm::vec3(0.0f, -sqrt(2), 0.0f)) *
                              glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    children.at(6)->transform(glm::translate(glm::vec3(1.5 * sqrt(2), 0.5 * sqrt(2), 0.0f)) *
                              glm::rotate(glm::radians(225.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
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
    for (int i = 0; i < children.size(); i++) {
        children.at(i)->draw(ModelMatrixId, BaseColorId);
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
