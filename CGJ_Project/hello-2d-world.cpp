////////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a TriangleVertex in Clip Space.
// A "Hello 2D World" of Modern OpenGL.
//
// Copyright (c) 2013-24 by Carlos Martinho
//
// INTRODUCES:
// GL PIPELINE, mglShader.hpp, mglConventions.hpp
//
////////////////////////////////////////////////////////////////////////////////
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>

#include "../mgl/mgl.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowCloseCallback(GLFWwindow *win) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;

 private:
  const GLuint POSITION = 0, COLOR = 1;
  GLuint VaoId[3], VboId[2];
  std::unique_ptr<mgl::ShaderProgram> Shaders;
  GLint MatrixId;

  void createShaderProgram();
  void createBufferObjects();
  void destroyBufferObjects();
  void drawScene();
};

//////////////////////////////////////////////////////////////////////// SHADERs

void MyApp::createShaderProgram() {
  Shaders = std::make_unique<mgl::ShaderProgram>();
  Shaders->addShader(GL_VERTEX_SHADER, "clip-vs.glsl");
  Shaders->addShader(GL_FRAGMENT_SHADER, "clip-fs.glsl");

  Shaders->addAttribute(mgl::POSITION_ATTRIBUTE, POSITION);
  Shaders->addAttribute(mgl::COLOR_ATTRIBUTE, COLOR);
  Shaders->addUniform("Matrix");

  Shaders->create();

  MatrixId = Shaders->Uniforms["Matrix"].index;
}

//////////////////////////////////////////////////////////////////// VAOs & VBOs

typedef struct {
  GLfloat XYZW[4];
  GLfloat RGBA[4];
} Vertex;

const Vertex triangleVertex[] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.0f, 0.5f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}};  //2

const GLubyte triangleIndices[] = { 0, 1, 2 };

const Vertex squareVertex[] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},   //1
    {{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},   //2
	{{0.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}}};  //3

const GLubyte squareIndices[] = { 0, 1, 2, 0, 2, 3};

const Vertex parallelogramVertex[] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   //1
    {{1.0f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},   //2
	{{0.5f, 0.5f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}};  //3

const GLubyte parallelogramIndices[] = { 0, 1, 2, 0, 2, 3};

void MyApp::createBufferObjects() {
  glGenVertexArrays(3, VaoId);
  glBindVertexArray(VaoId[0]);
  {
    glGenBuffers(2, VboId);

    glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
    {
      glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertex), triangleVertex, GL_STATIC_DRAW);
      glEnableVertexAttribArray(POSITION);
      glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            reinterpret_cast<GLvoid *>(0));
      glEnableVertexAttribArray(COLOR);
      glVertexAttribPointer(
          COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
          reinterpret_cast<GLvoid *>(sizeof(triangleVertex[0].XYZW)));
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
    {
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices,
                   GL_STATIC_DRAW);
    }
  }
  glBindVertexArray(VaoId[1]);
  {
      glGenBuffers(2, VboId);

      glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
      {
          glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertex), squareVertex, GL_STATIC_DRAW);
          glEnableVertexAttribArray(POSITION);
          glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
              reinterpret_cast<GLvoid*>(0));
          glEnableVertexAttribArray(COLOR);
          glVertexAttribPointer(
              COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
              reinterpret_cast<GLvoid*>(sizeof(squareVertex[0].XYZW)));
      }
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
      {
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices,
              GL_STATIC_DRAW);
      }
  }
  glBindVertexArray(VaoId[2]);
  {
	  glGenBuffers(2, VboId);

	  glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	  {
		  glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogramVertex), parallelogramVertex, GL_STATIC_DRAW);
		  glEnableVertexAttribArray(POSITION);
		  glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			  reinterpret_cast<GLvoid*>(0));
		  glEnableVertexAttribArray(COLOR);
		  glVertexAttribPointer(
			  COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			  reinterpret_cast<GLvoid*>(sizeof(parallelogramVertex[0].XYZW)));
	  }
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
	  {
		  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(parallelogramIndices), parallelogramIndices,
			  GL_STATIC_DRAW);
	  }
  }
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(2, VboId);
}

void MyApp::destroyBufferObjects() {
    for (int i = 0; i < 3; i++) {
        glBindVertexArray(VaoId[i]);
        glDisableVertexAttribArray(POSITION);
        glDisableVertexAttribArray(COLOR);
        glDeleteVertexArrays(1, VaoId);
    }
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////// SCENE

const glm::mat4 I(1.0f);
const glm::mat4 parallelogram = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 triangle = glm::translate(glm::vec3(-1.0f, -1.0f, 0.0f));

void MyApp::drawScene() {
  // Drawing directly in clip space

  glBindVertexArray(VaoId[0]);
  Shaders->bind();

  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(triangle));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
                 reinterpret_cast<GLvoid *>(0));

  glBindVertexArray(VaoId[1]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(I));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[2]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(parallelogram));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
	  reinterpret_cast<GLvoid*>(0));

  Shaders->unbind();
  glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
  createBufferObjects();
  createShaderProgram();
}

void MyApp::windowCloseCallback(GLFWwindow *win) { destroyBufferObjects(); }

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
  glViewport(0, 0, winx, winy);
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) { drawScene(); }

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char *argv[]) {
  mgl::Engine &engine = mgl::Engine::getInstance();
  engine.setApp(new MyApp());
  engine.setOpenGL(4, 6);
  engine.setWindow(600, 600, "Hello Modern 2D World", 0, 1);
  engine.init();
  engine.run();
  exit(EXIT_SUCCESS);
}

//////////////////////////////////////////////////////////////////////////// END