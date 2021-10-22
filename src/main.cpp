#include <array>

#include "Context.h"
#include "Program.h"

int main() {
    Context context;

    Program program;

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

    std::array<GLfloat, 2> position = {0.0f, 0.0f};

    while (!glfwWindowShouldClose(context.getWindow())) {
        glfwPollEvents();

        if (glfwGetKey(context.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            position[0] += 0.05;
        }

        if (glfwGetKey(context.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            position[0] -= 0.05;
        }

        int width, height;
        glfwGetFramebufferSize(context.getWindow(), &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.setTimeUniform(GLfloat(glfwGetTime()));
        program.setPositionUniform(position);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(context.getWindow());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}