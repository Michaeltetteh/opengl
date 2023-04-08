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
    Application app("Geometry Shader Normal Visualization");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader shader("shaders/normal_visualization/vertex_shader.glsl", "shaders/normal_visualization/frag_shader.glsl");
    Shader normalShader(
        "shaders/normal_visualization/normal_vertex_shader.glsl", 
        "shaders/normal_visualization/normal_frag_shader.glsl",
        "shaders/normal_visualization/normal_geometry_shader.glsl");

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
        glm::mat4 view = Application::camera.GetViewMatrix();;
        glm::mat4 model = glm::mat4(1.0f);
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);

        // draw model as usual
        nanosuit.Draw(shader);

        // then draw model with normal visualizing geometry shader
        normalShader.use();
        normalShader.setMat4("projection", projection);
        normalShader.setMat4("view", view);
        normalShader.setMat4("model", model);

        nanosuit.Draw(normalShader);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    return 0;
}
