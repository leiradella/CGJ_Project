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
  
    mgl::Mesh *Mesh = nullptr;
    InputManager *inputManager = nullptr;
    GLint BaseColorId;
    void createMeshes();
    void createShaderPrograms();
    void createCamera();
    void createInputManager();
    void drawScene();
};

///////////////////////////////////////////////////////////////////////// MESHES

void MyApp::createMeshes() {
  std::string mesh_dir = "../assets/";
  // std::string mesh_file = "cube-v.obj";
  // std::string mesh_file = "cube-vn-flat.obj";
  // std::string mesh_file = "cube-vn-smooth.obj";
  // std::string mesh_file = "cube-vt.obj";
  // std::string mesh_file = "cube-vt2.obj";
  // std::string mesh_file = "bunny-vn-smooth.obj";
  std::string mesh_file = "Parallelogram_piece_vn.obj";
  std::string mesh_fullname = mesh_dir + mesh_file;

  Mesh = new mgl::Mesh();
  Mesh->joinIdenticalVertices();
  Mesh->create(mesh_fullname);
}

///////////////////////////////////////////////////////////////////////// SHADER

void MyApp::createShaderPrograms() {
  Shaders = new mgl::ShaderProgram();
  Shaders->addShader(GL_VERTEX_SHADER, "cube-vs.glsl");
  Shaders->addShader(GL_FRAGMENT_SHADER, "cube-fs.glsl");

  Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);
  if (Mesh->hasNormals()) {
    Shaders->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);
  }
  if (Mesh->hasTexcoords()) {
    Shaders->addAttribute(mgl::TEXCOORD_ATTRIBUTE, mgl::Mesh::TEXCOORD);
  }
  if (Mesh->hasTangentsAndBitangents()) {
    Shaders->addAttribute(mgl::TANGENT_ATTRIBUTE, mgl::Mesh::TANGENT);
  }

  Shaders->addUniform("BaseColor");
  Shaders->addUniform(mgl::MODEL_MATRIX);
  Shaders->addUniformBlock(mgl::CAMERA_BLOCK, UBO_BP);
  Shaders->create();

  BaseColorId = Shaders->Uniforms["BaseColor"].index;
  ModelMatrixId = Shaders->Uniforms[mgl::MODEL_MATRIX].index;
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

glm::mat4 ModelMatrix(1.0f);

void MyApp::drawScene() {
    Shaders->bind();
    glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    Mesh->draw();
    Shaders->unbind();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    createMeshes();
    createShaderPrograms();  // after mesh;
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
