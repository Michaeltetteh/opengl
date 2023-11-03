#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include "GLFW/glfw3.h"
#include "glad.h"
#include <iostream>
#include <string>
#include "camera.h"


#define D_WIDTH  800
#define D_HEIGHT 600

float lastX = D_WIDTH / 2.0f;
float lastY = D_HEIGHT / 2.0f;
bool firstMouse = true;


bool blinn = false;
bool blinnKeyPressed = false;

bool shadows = true;
bool shadowsKeyPressed = false;

bool normal = false;
bool normalKeyPressed = false;

bool gammaEnabled = false;
bool gammaKeyPressed = false;

float heightScale = 0.1f;

bool lightColor = true;

// hdr
bool hdr = true;
bool hdrKeyPressed = false;
float exposure = 1.0f;

/**
 * Sets up opengl application(creates glfw window(s) and initializes glad)
 *
 * */
class Application
{
public:
    explicit Application(int width,int height,const std::string& title);
    explicit Application(const std::string& title="OpenGl Window");

    ~Application();

    static void frame_buffer_size_callback(GLFWwindow *window,int w,int h);

    void processInput() const;
    void processCameraInput() const;
    void processInputTextureMix(float &) const;


    static void mouse_callback(GLFWwindow *window,double xpos,double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow *window;

    //timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    static Camera camera;

private:
    void initGlfwGlad(const std::string& title, int width=D_WIDTH, int height=D_HEIGHT);

};

Camera Application::camera{glm::vec3(0.0f,0.0f,3.0f)};

void Application::initGlfwGlad(const std::string& title, int width, int height)
{
    //glfw window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(window == nullptr)
    {
        std::cout<<"Failed to create window"<<"\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Failed to initialized glad"<<"\n";
    }
}

Application::Application(const std::string& title)
{
    initGlfwGlad(title);
}

Application::Application( int width,int height,const std::string& title)
{
    initGlfwGlad(title, width, height);
}

void Application::frame_buffer_size_callback(GLFWwindow *window, int w, int h)
{
    glViewport(0,0,w,h);
}

Application::~Application()
{
    glfwTerminate();
}

void Application::processInput() const
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

}

void Application::processCameraInput() const
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD,deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed) 
    {
        blinn = !blinn;
        blinnKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) 
    {
        blinnKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !gammaKeyPressed) 
    {
        gammaEnabled = !gammaEnabled;
        gammaKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE) 
    {
        gammaKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !shadowsKeyPressed)
    {
        shadows = !shadows;
        shadowsKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        shadowsKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !normalKeyPressed)
    {
        normal = !normal;
        normalKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
    {
        normalKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
    {
        if (heightScale > 0.0f) 
            heightScale -= 0.0005f;
        else 
            heightScale = 0.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
    {
        if (heightScale < 1.0f) 
            heightScale += 0.0005f;
        else 
            heightScale = 1.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !hdrKeyPressed)
    {
        hdr = !hdr;
        hdrKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
    {
        hdrKeyPressed = false;
    }
}

void Application::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Application::processInputTextureMix(float &val) const
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

#endif
