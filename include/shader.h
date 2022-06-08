#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <string>
#include <iostream>

class Shader
{
public:
    unsigned int ID; //program id

    Shader(const char *vertexPath, const char *fragmentPath);
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif //OPENGL_SHADER_H
