#include <GLFW/glfw3.h>
#include "../../include/shader.h"
#include "../../include/application.h"
#include "../../include/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../include/utils.h"
#include "../../include/model.h"
//#include <glm/gtx/string_cast.hpp>


int main()
{
    Application app("Model Loading");
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    // build and compile shader program
    // ------------------------------------
    Shader ourShader("shaders/model/modelVertex.shader", "shaders/model/modelFrag.shader");

    // load models
    // -----------
    Model mModel("resources/objects/backpack/backpack.obj");

    // draw in wireframe
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        mModel.Draw(ourShader);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    return 0;
}