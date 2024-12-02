#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../mgl/mgl.hpp"

const GLuint POSITION = 0;

typedef struct {
    GLfloat XYZW[4];
} Vertex;

class Object2D {
public:
    GLuint vao;

    void createVao(const Vertex* vertex, size_t vertexNum, const GLubyte* index, size_t indexNum);
    void destroyVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId, size_t indexNum);
};

class Triangle : public Object2D {
public:
    static const Vertex vertex[3];
    static const GLubyte index[3];

    void createVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};

class Square : public Object2D {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];

    void createVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};

class Parallelogram : public Object2D {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];

    void createVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};