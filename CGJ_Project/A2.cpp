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
#include <cmath>
#include "../mgl/mgl.hpp"

#include "objects.hpp"

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowCloseCallback(GLFWwindow *win) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;

 private:
  const GLuint POSITION = 0, COLOR = 1;
  GLuint VaoId[7], VboId[2];
  std::unique_ptr<mgl::ShaderProgram> Shaders;
  GLint MatrixId;
  GLint ColorId;

  void createShaderProgram();
  void createBufferObjects();
  void addBufferTriangle(int i);
  void addBufferSquare(int i);
  void addBufferParallelogram(int i);
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
  Shaders->addUniform("Color");

  Shaders->create();

  MatrixId = Shaders->Uniforms["Matrix"].index;
  ColorId = Shaders->Uniforms["Color"].index;
}

//////////////////////////////////////////////////////////////////// VAOs & VBOs

void MyApp::createBufferObjects() {
    glGenVertexArrays(3, VaoId);
    addBufferTriangle(0);
    addBufferSquare(1);
    addBufferParallelogram(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, VboId);
}

void MyApp::addBufferTriangle(int i) {
    Triangle triangle;
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.vertex), triangle.vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle.index), triangle.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::addBufferSquare(int i) {
    Square square;
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(square.vertex), square.vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square.index), square.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::addBufferParallelogram(int i) {
    Parallelogram parallelogram;
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogram.vertex), parallelogram.vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(parallelogram.index), parallelogram.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::destroyBufferObjects() {
    for (int i = 0; i < 3; i++) {
        glBindVertexArray(VaoId[i]);
        glDisableVertexAttribArray(POSITION);
        glDeleteVertexArrays(1, VaoId);
    }
    glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////// SCENE

const glm::mat4 m1 = glm::translate(glm::vec3(-(0.5 - (0.25 * sqrt(2)) / 2), -(sqrt(pow(0.5, 2) / 2) + sqrt(pow(0.25, 2) / 2)), 0.0f))
                    * glm::scale(glm::vec3(0.5f, 0.5f, 1.0f))
                    * glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 m2 = glm::translate(glm::vec3(-0.5f, 0.0f, 0.0f))
                    * glm::scale(glm::vec3(1.0f, 1.0f, 1.0f))
                    * glm::rotate(glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 m3 = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f))
                    * glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 m4 = glm::translate(glm::vec3(0.07f, 0.0f, 0.0f))
                    * glm::scale(glm::vec3(0.5f, 0.5f, 1.0f))
                    * glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 m5 = glm::translate(glm::vec3(0.5f, -0.32f, 0.0f))
                    * glm::scale(glm::vec3(sqrt(2) * 0.5, sqrt(2) * 0.5, 1.0f))
                    * glm::rotate(glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
const glm::mat4 m6 = glm::translate(glm::vec3(0.0f, -0.25f, 0.0f))
                    * glm::scale(glm::vec3(0.5f, 0.5f, 1.0f));
const glm::mat4 m7 = glm::translate(glm::vec3(0.25f, 0.0f, 0.0f))
                    * glm::scale(glm::vec3(0.5f, 0.5f, 1.0f))
                    * glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

void MyApp::drawScene() {
  // Drawing directly in clip space

  glm::vec4 rgba;

  glBindVertexArray(VaoId[0]);
  Shaders->bind();

  rgba = { 0.9254901961f, 0.1098039216f, 0.1411764706f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m1));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
                 reinterpret_cast<GLvoid *>(0));

  rgba = { 0.2745098039f, 0.5882352941f, 0.9294117647f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m2));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  rgba = { 0.4431372549f, 0.7490196078f, 0.2705882353f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m3));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
	  reinterpret_cast<GLvoid*>(0));

  rgba = { 0.8274509804f, 0.831372549f, 0.8392156863f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m4));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  rgba = { 0.9568627451f, 0.5137254902f, 0.1215686275f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m5));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[1]);
  rgba = { 1.0f, 0.7607843137f, 0.05882352941f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m6));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[2]);
  rgba = { 0.6862745098f, 0.5960784314f, 0.8274509804f, 1.0f };
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m7));
  glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
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
