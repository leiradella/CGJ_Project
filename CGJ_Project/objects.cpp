#include "objects.hpp"


//////////////////////////////////////////////////////////////////////TRIANGLE
const Vertex Triangle::vertex[3] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //2

const GLubyte Triangle::index[3] = { 0, 1, 2 };

void Triangle::createVao() {
    GLuint vboId[2];

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    {
        glGenBuffers(2, vboId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex), this->vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->index), this->index,
                GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, vboId);
}

void Triangle::destroyVao() {
    glBindVertexArray(this->vao);
    glDisableVertexAttribArray(POSITION);
    glDeleteVertexArrays(1, &this->vao);
}

void Triangle::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    glBindVertexArray(this->vao);
    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));
}


//////////////////////////////////////////////////////////////////////SQUARE
const Vertex Square::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.5f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Square::index[6] = { 0, 1, 2, 0, 2, 3 };

void Square::createVao() {
    GLuint vboId[2];

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    {
        glGenBuffers(2, vboId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex), this->vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->index), this->index,
                GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, vboId);
}

void Square::destroyVao() {
    glBindVertexArray(this->vao);
    glDisableVertexAttribArray(POSITION);
    glDeleteVertexArrays(1, &this->vao);
}

void Square::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    glBindVertexArray(this->vao);
    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));
}

//////////////////////////////////////////////////////////////////////PARALLELOGRAM
const Vertex Parallelogram::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{1.0f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.5f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Parallelogram::index[6] = { 0, 1, 2, 0, 2, 3 };

void Parallelogram::createVao() {
    GLuint vboId[2];

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    {
        glGenBuffers(2, vboId);

        glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex), this->vertex, GL_STATIC_DRAW);
            glEnableVertexAttribArray(POSITION);
            glVertexAttribPointer(POSITION, 4, GL_FLOAT, GL_FALSE, 0,
                reinterpret_cast<GLvoid*>(0));
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId[1]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->index), this->index,
                GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, vboId);
}

void Parallelogram::destroyVao() {
    glBindVertexArray(this->vao);
    glDisableVertexAttribArray(POSITION);
    glDeleteVertexArrays(1, &this->vao);
}

void Parallelogram::draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId) {
    glBindVertexArray(this->vao);
    glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(matrix));
    glUniform4fv(ColorId, 1, glm::value_ptr(rgba));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
        reinterpret_cast<GLvoid*>(0));
}