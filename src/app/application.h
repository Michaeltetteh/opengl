#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H
#include "GLFW/glfw3.h"
#include "../../libs/glad/glad.h"
#include <iostream>
#include <string>
#include "camera.h"


const unsigned int D_WIDTH = 800;
const unsigned int D_HEIGHT = 600;
float lastX = D_WIDTH / 2.0f;
float lastY = D_HEIGHT / 2.0f;
bool firstMouse = true;


bool blinn = false;
bool blinnKeyPressed = false;

/**
 * Sets up opengl application(creates glfw window(s) and initializes glad)
 *
 * */
class Application
{
public:
    [[maybe_unused]] Application(int width,int height,const std::string& title);

    [[maybe_unused]] explicit Application(const std::string& title="OpenGl Window");
    ~Application();

    static void frame_buffer_size_callback([[maybe_unused]] GLFWwindow *window,int w,int h);

    [[maybe_unused]] void processInput() const;

    [[maybe_unused]] void processCameraInput() const;

    [[maybe_unused]] void processInputTextureMix(float &) const;
    static void mouse_callback([[maybe_unused]] GLFWwindow *window,double xpos,double ypos);
    static void scroll_callback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double xoffset, double yoffset);

    GLFWwindow *window;

    //timing
    float deltaTime = 0.0f;
    [[maybe_unused]] float lastFrame = 0.0f;


    static Camera camera;

};

Camera Application::camera{glm::vec3(0.0f,0.0f,3.0f)};

[[maybe_unused]] Application::Application(const std::string& title)
{
    //glfw window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    
    window = glfwCreateWindow(D_WIDTH,D_HEIGHT,title.c_str(),nullptr,nullptr);
    if(window == nullptr)
    {
        std::cout<<"Failed to create window"<<"\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Failed to initialized glad"<<"\n";
    }

}

[[maybe_unused]] Application::Application( int width,int height,const std::string& title)
{
    //glfw window setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    window = glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr);
    if(window == nullptr)
    {
        std::cout<<"Failed to create window"<<"\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Failed to initialized glad"<<"\n";
    }


}

void Application::frame_buffer_size_callback([[maybe_unused]] GLFWwindow *window, int w, int h)
{
    glViewport(0,0,w,h);
}

Application::~Application()
{
    glfwTerminate();
}

[[maybe_unused]] void Application::processInput() const
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

}

[[maybe_unused]] void Application::processCameraInput() const
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
}

void Application::mouse_callback([[maybe_unused]] GLFWwindow *window, double xposIn, double yposIn)
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

void Application::scroll_callback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

[[maybe_unused]] void Application::processInputTextureMix(float &val) const
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
