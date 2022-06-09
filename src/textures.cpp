#include <GLFW/glfw3.h>
#include "../include/shader.h"
#include "../include/application.h"
#include "../include/stb_image.h"


int main()
{
    Application app(800,600,"App Window");

    Shader shader(
            "/Users/mike/Desktop/cpp_projects/opengl/src/shaders/texVertex.shader",
            "/Users/mike/Desktop/cpp_projects/opengl/src/shaders/textureFrag.shader"
    );

    float vertices[] ={
            //          positions          ||            colors             ||  texture coordinates
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,        // top right
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };


    //creating and binding vertex array object
    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    //creating memory in the GPU for the vertex data to be stored
    glGenBuffers(1,&VBO);


    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //linking vertex attributes
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0); //enable vertex attrib 0(location =0)

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),
                    (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); //vertex attrib 1

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //add texture
    int width,height,nChannels;
    unsigned char *data = stbi_load(
            "/Users/mike/Desktop/cpp_projects/opengl/resources/textures/container.jpg",
            &width,
            &height,
            &nChannels,
            0);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Failed to load texture"<<"\n";
    }
    stbi_image_free(data);


    while (!glfwWindowShouldClose(app.window))
    {
        app.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D,texture);
        //use program
        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(app.window);
        glfwPollEvents();

    }

    //deallocate all resources
    glDeleteProgram(shader.getProgram());
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);



    return 0;
}