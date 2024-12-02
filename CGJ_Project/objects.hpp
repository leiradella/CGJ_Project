#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../mgl/mgl.hpp"

const GLuint POSITION = 0;

typedef struct {
    GLfloat XYZW[4];
} Vertex;

class Triangle {
public:
    static const Vertex vertex[3];
    static const GLubyte index[3];
    GLuint vao;


    void createVao();
    void destroyVao();

    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};

class Square {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];
    GLuint vao;

    void createVao();
    void destroyVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};

class Parallelogram {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];
    GLuint vao;

    void createVao();
    void destroyVao();
    void draw(glm::vec4 rgba, glm::mat4 matrix, GLint MatrixId, GLint ColorId);
};