#include <GLFW/glfw3.h>
#include "../include/shader.h"
#include "../include/application.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

int main()
{
    Application app(800,600,"App Window");

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

    while (!glfwWindowShouldClose(app.window))
    {
        processInput(app.window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //use program
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(app.window);
        glfwPollEvents();

    }

    //deallocate all resources
    glDeleteProgram(shader.getProgram());
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);



    return 0;
}