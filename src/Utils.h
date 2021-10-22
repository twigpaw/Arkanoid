#ifndef ARKANOID_UTILS_H
#define ARKANOID_UTILS_H

#include <string>
#include <glad.h>

using std::string;

class Utils {
public:
    Utils() = delete;

    static string getStringFromFile(const string &fileName);

    static GLuint loadShader(int shaderType, const string &fileName);
};

#endif //ARKANOID_UTILS_H