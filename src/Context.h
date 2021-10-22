#ifndef ARKANOID_CONTEXT_H
#define ARKANOID_CONTEXT_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using std::string;

class Context {
public:
    Context();

    GLFWwindow* getWindow();

private:
    GLFWwindow* window;

    GLFWwindow* initWindow();

    static void errorCallback(int error, const char* description);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif //ARKANOID_CONTEXT_H