#include "Program.h"

#include <iostream>

#include "Utils.h"

Program::Program() {
    init();
}

void Program::init() {
    GLuint vertexShader   = Utils::loadShader(GL_VERTEX_SHADER,   "../res/shaders/basic.vsh");
    GLuint fragmentShader = Utils::loadShader(GL_FRAGMENT_SHADER, "../res/shaders/basic.fsh");

    handle = glCreateProgram();
    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    glBindAttribLocation(handle, 0, "a_position");
    glLinkProgram(handle);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(handle, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(handle);

    timeUniform = glGetUniformLocation(handle, "u_time");
    positionUniform = glGetUniformLocation(handle, "u_position");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Program::setTimeUniform(GLfloat time) const {
    glUniform1f(timeUniform, time);
}

void Program::setPositionUniform(const std::array<GLfloat, 2> &position) const {
    glUniform2fv(positionUniform, 1, position.data());
}