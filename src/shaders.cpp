#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include <string>
#include <algorithm>
#include <cmath>
#include "../include/shader.h"
//#include <filesystem> //path c++17


void frame_buffer_size_callback(GLFWwindow *window,int w,int h)
{
    glViewport(0,0,w,h);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}


int main()
{
    //glfw window setup
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
//    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    //Glad initialization
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<<"Failed to initialized glad"<<"\n";
        return -1;
    }

    Shader shader(
        "/Users/mike/Desktop/cpp_projects/opengl/src/shaders/vertex_shader.shader",
        "/Users/mike/Desktop/cpp_projects/opengl/src/shaders/fragment_shader.shader"
    );


    float vertices[] ={
            -0.2f,-0.2f,0.0f,1.0f,0.0f,0.0f,
            0.2f,-0.2f,0.0f,0.0f,1.0f,0.0f,
            0.0f,0.2f,0.0f,0.0f,0.0f,1.0f
    };


    //creating and binding vertex array object
    unsigned int VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    //creating memory in the GPU for the vertex data to be stored
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //linking vertex attributes
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0); //enable vertex attrib 0(location =0)

    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            6*sizeof(float),
            (void*)(3*sizeof(float)) //starting position  in the vertices array [3]
    );
    glEnableVertexAttribArray(1); //vertex attrib 1



    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //use program
        shader.use();

        //color gradient
//        float timeVal = glfwGetTime();
//        float greenValue = (sin(timeVal) /2.0f) + 0.5f;
        //std::cout<<"Time(s): "<<timeVal<<" greenval: "<<greenValue<<"Sine(t): "<< sin(timeVal)<<"\n";
//        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");

        //                  uniform location        R          G           B          A
        //glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //deallocate all resources
    glDeleteProgram(shader.getProgram());
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);

    glfwTerminate();


    return 0;
}