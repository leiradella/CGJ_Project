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

  void createShaderProgram();
  void createBufferObjects();
  void addBufferTriangle(int i, float r, float g, float b, float a);
  void addBufferSquare(int i, float r, float g, float b, float a);
  void addBufferParallelogram(int i, float r, float g, float b, float a);
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

void MyApp::createBufferObjects() {
    glGenVertexArrays(7, VaoId);
    addBufferTriangle(0, 0.9254901961f, 0.1098039216f, 0.1411764706f, 1.0f);
    addBufferTriangle(1, 0.2745098039f, 0.5882352941f, 0.9294117647f, 1.0f);
    addBufferTriangle(2, 0.4431372549f, 0.7490196078f, 0.2705882353f, 1.0f);
    addBufferTriangle(3, 0.8274509804f, 0.831372549f, 0.8392156863f, 1.0f);
    addBufferTriangle(4, 0.9568627451f, 0.5137254902f, 0.1215686275f, 1.0f);
    addBufferSquare(5, 1.0f, 0.7607843137f, 0.05882352941f, 1.0f);
    addBufferParallelogram(6, 0.6862745098f, 0.5960784314f, 0.8274509804f, 1.0f);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, VboId);
}

void MyApp::addBufferTriangle(int i, float r, float g, float b, float a) {
    Triangle triangle;
    GLfloat rgba[] = {r, g, b, a};
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.vertex) + sizeof(rgba) * 3, NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle.vertex), triangle.vertex);
            for (int i = 0; i < 3; i++) {
                glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle.vertex) + sizeof(rgba) * i, sizeof(rgba), rgba);
            }
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
            glEnableVertexAttribArray(COLOR);
            glVertexAttribPointer(
                COLOR, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(sizeof(triangle.vertex)));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle.index), triangle.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::addBufferSquare(int i, float r, float g, float b, float a) {
    Square square;
    GLfloat rgba[] = { r, g, b, a };
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(square.vertex) + sizeof(rgba) * 4, NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(square.vertex), square.vertex);
            for (int i = 0; i < 4; i++) {
                glBufferSubData(GL_ARRAY_BUFFER, sizeof(square.vertex) + sizeof(rgba) * i, sizeof(rgba), rgba);
            }
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
            glEnableVertexAttribArray(COLOR);
            glVertexAttribPointer(
                COLOR, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(sizeof(square.vertex)));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square.index), square.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::addBufferParallelogram(int i, float r, float g, float b, float a) {
    Parallelogram parallelogram;
    GLfloat rgba[] = { r, g, b, a };
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(2, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogram.vertex) + sizeof(rgba) * 4, NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(parallelogram.vertex), parallelogram.vertex);
            for (int i = 0; i < 4; i++) {
                glBufferSubData(GL_ARRAY_BUFFER, sizeof(parallelogram.vertex) + sizeof(rgba) * i, sizeof(rgba), rgba);
            }
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
            glEnableVertexAttribArray(COLOR);
            glVertexAttribPointer(
                COLOR, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(sizeof(parallelogram.vertex)));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(parallelogram.index), parallelogram.index,
                GL_STATIC_DRAW);
        }
    }
}

void MyApp::destroyBufferObjects() {
    for (int i = 0; i < 6; i++) {
        glBindVertexArray(VaoId[i]);
        glDisableVertexAttribArray(POSITION);
        glDisableVertexAttribArray(COLOR);
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

  glBindVertexArray(VaoId[0]);
  Shaders->bind();

  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m1));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
                 reinterpret_cast<GLvoid *>(0));

  glBindVertexArray(VaoId[1]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m2));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[2]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m3));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
	  reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[3]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m4));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[4]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m5));
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[5]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m6));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
      reinterpret_cast<GLvoid*>(0));

  glBindVertexArray(VaoId[6]);
  glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(m7));
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
