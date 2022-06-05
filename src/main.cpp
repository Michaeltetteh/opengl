#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800,600,"OpenGl Window",NULL,NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to create window"<<"\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    return 0;
}