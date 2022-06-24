#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;

    unsigned int getProgram() const;

private:
    unsigned int ID; //program id


};

#endif //OPENGL_SHADER_H
