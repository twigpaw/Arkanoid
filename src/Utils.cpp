#include "Utils.h"

#include <fstream>
#include <sstream>
#include <iostream>

string Utils::getStringFromFile(const string &fileName) {
    std::ifstream fileStream;
    fileStream.open(fileName);
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    string res = stringStream.str();
    return res;
}

GLuint Utils::loadShader(int shaderType, const string &fileName) {
    GLuint shader = glCreateShader(shaderType);

    string shaderSource = getStringFromFile(fileName);
    auto str = shaderSource.c_str();
    glShaderSource(shader, 1, &str, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(success) {
        std::cout << "Shader loaded" << std::endl;
    } else {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}