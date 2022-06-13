#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include <iostream>
#include <string>

/**
 * Sets up opengl application(creates glfw window(s) and initializes glad)
 *
 * */
class Application
{
public:
    Application(int width,int height,std::string title);
    ~Application();

    static void frame_buffer_size_callback(GLFWwindow *window,int w,int h);
    void processInput();
    void processInputTextureMix(float &);


    GLFWwindow *window;

};

Application::Application(int width, int height,std::string title="OpenGl Window")
{

    //glfw window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    window = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to create window"<<"\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Failed to initialized glad"<<"\n";
    }
}

void Application::frame_buffer_size_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0,0,w,h);
}

Application::~Application()
{
    glfwTerminate();
}

void Application::processInput()
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

}

void Application::processInputTextureMix(float &val)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
    {
        val += 0.001f;
        if(val >= 1.0f)
            val = 1.0f;
    }
    if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        val -= 0.001f;
        if(val <= 0.0f)
            val = 0.0f;
    }
}

#endif //OPENGL_APPLICATION_H
