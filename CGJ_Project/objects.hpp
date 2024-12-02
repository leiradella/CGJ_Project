#include "../mgl/mgl.hpp"

typedef struct {
    GLfloat XYZW[4];
} Vertex;

class Triangle {
public:
    static const Vertex vertex[3];
    static const GLubyte index[3];
    GLfloat rgba[4];
};

class Square {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];
    GLfloat rgba[4];
};

class Parallelogram {
public:
    static const Vertex vertex[4];
    static const GLubyte index[6];
    GLfloat rgba[4];
};