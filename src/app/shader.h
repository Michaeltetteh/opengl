#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <fstream>
#include <sstream>
#include "glad.h"
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
    void setVec3(const std::string &name, glm::vec3 value) const;

    unsigned int getProgram() const;

private:
    unsigned int ID; //program id


};




void check_shader_compilation_errors(GLuint shader,std::string shader_type)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::transform(shader_type.begin(),shader_type.end(),shader_type.begin(),::toupper);
        std::cout << "ERROR::SHADER::"<<shader_type<<"::COMPILATION_FAILED\n" << infoLog << "\n";
    }
}

void check_program_link_error(GLuint program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(program,512,NULL,infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }
}



Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexShaderCode, fragmentShaderCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;

    //ensure ifstream objs can throw exceptions
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        //open vertex and fragment files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        //read file buffer content into string streams
        std::stringstream vertexStream,fragmentStream;
        vertexStream << vertexShaderFile.rdbuf();
        fragmentStream << fragmentShaderFile.rdbuf();

        //close opened files
        fragmentShaderFile.close();
        vertexShaderFile.close();

        //convert stream into string and assign results to respective code var
        vertexShaderCode = vertexStream.str();
        fragmentShaderCode = fragmentStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"<<"\n";
    }

    //convert c++ string to compatible C type char*
    const char *vShaderCode = vertexShaderCode.c_str();
    const char *fShaderCode = fragmentShaderCode.c_str();

    //compile shaders
    unsigned int vShader,fShader;

    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader,1,&vShaderCode,NULL);
    glCompileShader(vShader);
    check_shader_compilation_errors(vShader,"vertex");

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader,1,&fShaderCode,NULL);
    glCompileShader(fShader);
    check_shader_compilation_errors(fShader,"fragment");

    //create shader program and attach shader
    ID = glCreateProgram();
    glAttachShader(ID,vShader);
    glAttachShader(ID,fShader);
    glLinkProgram(ID);
    check_program_link_error(ID);

    //delete shaders
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&value[0][0]);
}
void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

unsigned int Shader::getProgram() const
{
    return ID;
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

#endif //OPENGL_SHADER_H
