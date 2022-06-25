#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H
#include <GLFW/glfw3.h>
#include "glad/glad.h"
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
    void processCameraInput();
    void processInputTextureMix(float &);
    static void mouse_callback(GLFWwindow *window,double xpos,double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow *window;
    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    static float lastX, lastY;
    static float yaw,pitch;
    static bool firstMouse;
    static float fov;
};

float Application::lastX = 400;
float Application::lastY = 300;
float Application::yaw = -90.0f;
float Application::pitch = 0.0f;
bool Application::firstMouse = true;
float Application::fov = 45.0f;

glm::vec3 Application::cameraPos = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 Application::cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 Application::cameraUp = glm::vec3(0.0f,1.0f,0.0f);

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
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window,mouse_callback);

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

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

}

void Application::processCameraInput()
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    const float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Application::mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastY = ypos;
    lastX = xpos;

    const float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
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
