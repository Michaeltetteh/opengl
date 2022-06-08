#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include <string>
#include <algorithm>
#include <cmath>

void frame_buffer_size_callback(GLFWwindow *window,int w,int h)
{
    glViewport(0,0,w,h);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

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

void check_program_compilation_error(GLuint program)
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


const char *vertex_shader =
        "#version 330 core \n"
        "layout (location=0) in vec3 pos;\n"
        "out vec4 fragColor2;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(pos, 1.0);\n"
        "   //fragColor2 = vec4(1.0f, 1.0f, 0.0f, 0.0f);\n"
        "}\n";

const char *fragment_shader =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main(){\n"
        " fragColor = ourColor;\n"
        "}\n";


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

//    int vertex_attrib;
//    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&vertex_attrib);
//    std::cout<<"Maximum number of vertex attributes supported: "<<vertex_attrib<<"\n";
    //compiling and linking shaders to shader program
    unsigned int vertexShader,fragmentShader,shaderProgram,fragmentShader2,shaderProgram2;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //attach shader source to the shader object and compile
    glShaderSource(vertexShader,1,&vertex_shader,NULL);
    glCompileShader(vertexShader);

    //check for errors in vertex shader compilation if any
    check_shader_compilation_errors(vertexShader,"vertex");

    //compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragment_shader,NULL);
    glCompileShader(fragmentShader);

    //check for fragment shader compilation errors
    check_shader_compilation_errors(fragmentShader,"fragment");

    //linking shader to a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //check program link errors
    check_program_compilation_error(shaderProgram);

    //delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    float vertices[] ={
            -0.2f,-0.2f,0.0f,
            0.2f,-0.2f,0.0f,
            0.0f,0.2f,0.0f
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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);



//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeVal = glfwGetTime();
        float greenValue = (sin(timeVal) /2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");

        //use program
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //deallocate all resources
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);

    glfwTerminate();


    return 0;
}