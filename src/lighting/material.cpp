#include <GLFW/glfw3.h>
#include "../../include/shader.h"
#include "../../include/application.h"
#include "../../include/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/string_cast.hpp>

float vertices[] = {
        //        vertex                ||  normal   || texture coordinates
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec3 LIGHTCOLOR = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);


struct Emerald{
    glm::vec3 ambient = glm::vec3(0.0215f,0.1745f,0.0215f);
    glm::vec3 diffuse = glm::vec3(	0.07568f,0.61424f,0.07568f);
    glm::vec3 specular = glm::vec3(0.633f,0.727811f,0.633f);
    float shininess = 0.6f * 128;
};

int main()
{
    Application app("Lighting");

    glEnable(GL_DEPTH_TEST);

    // build and compile shader program
    // ------------------------------------
    Shader cubeShader("shaders/material/cubeVertex.shader","shaders/material/cubeFrag.shader");
    Shader lightShader("shaders/material/lightVertex.shader","shaders/material/lightFrag.shader");

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //light VAO
    glGenVertexArrays(1, &LIGHTSRCVAO);
    glBindVertexArray(LIGHTSRCVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(app.window))
    {
        // input
        // -----
        auto currentFrame = static_cast<float>(glfwGetTime());
        app.deltaTime = currentFrame - app.lastFrame;
        app.lastFrame = currentFrame;

        app.processCameraInput();

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //CUBE
        cubeShader.use();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 1.0f,100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,(float)glfwGetTime() * glm::radians(40.0f),glm::vec3(0.0f,1.0f,0.0f));

        cubeShader.setVec3("ObjectColor",glm::vec3(1.0f, 0.5f, 0.31f));
        cubeShader.setVec3("LightColor",LIGHTCOLOR);
        cubeShader.setVec3("LightPosition",lightPos);
        cubeShader.setMat4("view",view);
        cubeShader.setMat4("projection",projection);
        cubeShader.setVec3("ViewPosition",Application::camera.Position);
        cubeShader.setMat4("model",model);

//        cubeShader.setVec3("material.ambient",glm::vec3(1.0f, 0.5f, 0.31f));
//        cubeShader.setVec3("material.diffuse",glm::vec3(1.0f, 0.5f, 0.31f));
//        cubeShader.setVec3("material.specular",glm::vec3( 0.5f, 0.5f, 0.5f));
//        cubeShader.setFloat("material.shininess",32.0f);
//        glm::vec3 turquoise_ambient = glm::vec3(0.1f,0.18725f,0.1745f);
//        glm::vec3 turquoise_diffuse = glm::vec3(0.396f,0.74151f,0.69102f);
//        glm::vec3 turquoise_specular = glm::vec3(0.297254f,0.30829f,0.306678f);

        Emerald emerald;
        cubeShader.setVec3("material.ambient",emerald.ambient);
        cubeShader.setVec3("material.diffuse",emerald.diffuse);
        cubeShader.setVec3("material.specular",emerald.specular);
        cubeShader.setFloat("material.shininess",emerald.shininess);

        glm::vec3 lightColor;
        lightColor.x = (float)glm::sin(glfwGetTime() * 2.0f);
        lightColor.y = (float)glm::sin(glfwGetTime() * 0.7f);
        lightColor.z = (float)glm::sin(glfwGetTime() * 1.3f);
        glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);

        cubeShader.setVec3("light.ambient",glm::vec3(1.0f));
        cubeShader.setVec3("light.diffuse",glm::vec3(1.0f));
        cubeShader.setVec3("light.specular",glm::vec3(1.0f));
        cubeShader.setVec3("light.position",lightPos);
        //cubeShader.setVec3("Color",glm::vec3(1.0f, 0.5f, 0.31f));
        glBindVertexArray(CUBEVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        //Light source
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.setMat4("view",view);
        lightShader.setMat4("projection",projection);
        lightShader.setVec3("LColor",LIGHTCOLOR);
        //lightShader.setVec3("LColor",diffuseColor);
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