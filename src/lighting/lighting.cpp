#include <GLFW/glfw3.h>
#include "../app/shader.h"
#include "../app/application.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../app/utils.h"



float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
};

glm::vec3 LIGHTCOLOR = glm::vec3(1.0f);

int main()
{
    Application app("Lighting");

    glEnable(GL_DEPTH_TEST);

    // build and compile shader program
    // ------------------------------------
    Shader cubeShader("shaders/lighting_scene/cubeVertex.shader","shaders/lighting_scene/cubeFrag.shader");
    Shader lightShader("shaders/lighting_scene/lightVertex.shader","shaders/lighting_scene/lightFrag.shader");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO, CUBEVAO,LIGHTSRCVAO;
    glGenBuffers(1, &VBO);

    // cube VAO
    glGenVertexArrays(1, &CUBEVAO);
    glBindVertexArray(CUBEVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //light VAO
    glGenVertexArrays(1, &LIGHTSRCVAO);
    glBindVertexArray(LIGHTSRCVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(app.window))
    {
        // input
        // -----
        app.processCameraInput();
        auto currentFrame = static_cast<float>(glfwGetTime());
        app.deltaTime = currentFrame - app.lastFrame;
        app.lastFrame = currentFrame;

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //CUBE
        cubeShader.use();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 1.0f,100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        cubeShader.setMat4("view",view);
        cubeShader.setMat4("projection",projection);
        cubeShader.setMat4("model",model);
        //cubeShader.setVec3("Color",glm::vec3(1.0f, 0.5f, 0.31f));
        cubeShader.setVec3("ObjectColor",glm::vec3(1.0f, 0.5f, 0.31f));
        cubeShader.setVec3("LightColor",LIGHTCOLOR);

        glBindVertexArray(CUBEVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        //Light source
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("view",view);
        lightShader.setMat4("projection",projection);
        lightShader.setVec3("LColor",LIGHTCOLOR);
        lightShader.setMat4("model",model);

        glBindVertexArray(LIGHTSRCVAO);
        glDrawArrays(GL_TRIANGLES,0,36);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &CUBEVAO);
    glDeleteVertexArrays(1, &LIGHTSRCVAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}