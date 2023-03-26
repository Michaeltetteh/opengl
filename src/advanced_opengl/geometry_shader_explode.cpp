#include <GLFW/glfw3.h>
#include "../app/shader_g.h"
#include "../app/application.h"
#include "../app/model_g.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
    Application app("Geometry Shader Explode");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader shader(
            "shaders/geometry_shader_explode/vertex_shader.glsl",
            "shaders/geometry_shader_explode/fragment_shader.glsl",
            "shaders/geometry_shader_explode/geometry_shader.glsl");

    // load models
    // -----------
    Model nanosuit("resources/objects/nanosuit/nanosuit.obj"); 

    // render loop
    // -----------
    while (!glfwWindowShouldClose(app.window))
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        app.deltaTime = currentFrame - app.lastFrame;
        app.lastFrame = currentFrame;

        // input
        // -----
        app.processCameraInput();


        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // configure transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);

        // add time component to geometry shader in the form of a uniform
        shader.setFloat("time", static_cast<float>(glfwGetTime()));

        // draw model
        nanosuit.Draw(shader);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    return 0;
}
