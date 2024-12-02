#include "objects.hpp"


void Object2D::createVao(const Vertex* vertex, size_t vertexNum, const GLubyte* index, size_t indexNum) {
    GLuint vboId[2];

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    {
        glGenBuffers(2, vboId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexNum, vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*indexNum, index,
                GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, vboId);
}

void Object2D::destroyVao() {
    glBindVertexArray(vao);
    glDisableVertexAttribArray(POSITION);
    glDeleteVertexArrays(1, &vao);
}

void Object2D::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId, size_t indexNum) {
    glBindVertexArray(vao);
    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
    glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));
}

//////////////////////////////////////////////////////////////////////TRIANGLE
const Vertex Triangle::vertex[3] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //2

const GLubyte Triangle::index[3] = { 0, 1, 2 };

void Triangle::createVao() {
    Object2D::createVao(vertex, 3, index, 3);
}

void Triangle::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    Object2D::draw(rgba, matrix, MatrixId, ColorId, 3);
}

//////////////////////////////////////////////////////////////////////SQUARE
const Vertex Square::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.5f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Square::index[6] = { 0, 1, 2, 0, 2, 3 };

void Square::createVao() {
    Object2D::createVao(vertex, 4, index, 6);
}

void Square::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    Object2D::draw(rgba, matrix, MatrixId, ColorId, 6);
}

//////////////////////////////////////////////////////////////////////PARALLELOGRAM
const Vertex Parallelogram::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{1.0f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.5f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Parallelogram::index[6] = { 0, 1, 2, 0, 2, 3 };

void Parallelogram::createVao() {
    Object2D::createVao(vertex, 4, index, 6);
}

void Parallelogram::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    Object2D::draw(rgba, matrix, MatrixId, ColorId, 6);
}