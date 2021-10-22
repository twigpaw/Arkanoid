#ifndef ARKANOID_PROGRAM_H
#define ARKANOID_PROGRAM_H

#include <array>

#include "glad.h"

class Program {
public:
    Program();

    void init();

    void setTimeUniform(GLfloat time) const;

    void setPositionUniform(const std::array<GLfloat, 2> &position) const;

private:
    GLuint handle;

    GLint timeUniform;
    GLint positionUniform;
};

#endif //ARKANOID_PROGRAM_H