#include <GLFW/glfw3.h>
#include "../../include/shader.h"
#include "../../include/application.h"
#include "../../include/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/string_cast.hpp>

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


int main()
{
    Application app("Lighting");

    glEnable(GL_DEPTH_TEST);

    // build and compile shader program
    // ------------------------------------
    Shader cubeShader("shaders/cubeVertex.shader","shaders/cubeFrag.shader");
    Shader lightShader("shaders/lightVertex.shader","shaders/lightFrag.shader");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    unsigned int VBO, CUBEVAO,LIGHTSRCVAO;
    glGenVertexArrays(1, &CUBEVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(CUBEVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

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
        glm::mat4 projection = glm::mat4 (1.0f);
        projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 1.0f,100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        cubeShader.setMat4("view",view);
        cubeShader.setMat4("projection",projection);
        cubeShader.setMat4("model",model);
        cubeShader.setVec3("Color",glm::vec3(1.0f, 0.5f, 0.31f));
        glDrawArrays(GL_TRIANGLES,0,36);

        //Light source
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("view",view);
        lightShader.setMat4("projection",projection);
        lightShader.setVec3("LColor",glm::vec3(1.0f, 1.0f, 1.0f));
        lightShader.setMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &CUBEVAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}