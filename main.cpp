#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::string;

struct StringHelper {
    const char *p;
    explicit StringHelper(const std::string& s) : p(s.c_str()) {}
    operator const char**() { return &p; }
};

GLuint program;

string getStringFromFile(const string &fileName) {
    std::ifstream fileStream;
    fileStream.open(fileName);
    std::stringstream stringStream;
    stringStream << fileStream.rdbuf();
    string res = stringStream.str();
    return res;
}

GLuint loadShader(int shaderType, const string &fileName) {
    string shaderSource = getStringFromFile(fileName);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, StringHelper(shaderSource), nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(success) {
        std::cout << "Shader loaded" << std::endl;
    } else {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLint timeUniform;
GLint positionUniform;

GLfloat position[2] = {0.2f, 0.3f};

GLuint createShaderProgram() {
    GLuint vertexShader   = loadShader(GL_VERTEX_SHADER,   "../basic.vsh");
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, "../basic.fsh");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram, 0, "a_position");
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    timeUniform = glGetUniformLocation(shaderProgram, "u_time");
    positionUniform = glGetUniformLocation(shaderProgram, "u_position");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

static void errorCallback(int error, const char* description) {
    std::cout << "Error: " << error << ' ' << description << std::endl;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        program = createShaderProgram();

    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        position[0] += 0.05;
    }

}

GLFWwindow* initWindow() {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Arkanoid", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    return window;
}

int main() {
    auto window = initWindow();

    program = createShaderProgram();

    GLfloat vertices[] {
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f, -0.5f,
        -0.5f,  0.5f
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(vertices[0]), nullptr);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(timeUniform, (GLfloat) glfwGetTime());
        glUniform2fv(positionUniform, 1, position);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}