#include <GLFW/glfw3.h>
#include "../../include/shader.h"
#include "../../include/application.h"
#include "../../include/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "../../include/utils.h"
#include "../../include/model.h"
//#include <glm/gtx/string_cast.hpp>


int main()
{
    Application app("Model Loading");
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    // build and compile shader program
    // ------------------------------------
    Shader cyborgShader("shaders/model/modelVertex.shader", "shaders/model/modelFrag.shader");
    Shader sunShader("shaders/model/sunV.shader", "shaders/model/sunF.shader");

    // load models
    // -----------
//    Model mModel("resources/objects/backpack/backpack.obj");
    Model CyborgModel("resources/objects/cyborg/cyborg.obj");
    Model sunModel("resources/objects/Sun/Sun.obj");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

        cyborgShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(Application::camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view = Application::camera.GetViewMatrix();
        cyborgShader.setMat4("projection", projection);
        cyborgShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        //ourShader.setMat4("model", model);
        //mModel.Draw(ourShader);

        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        cyborgShader.setMat4("model", model);
        CyborgModel.Draw(cyborgShader);

        model = glm::translate(model, glm::vec3(-4.0f,  2.0f, -12.0f));
        model = glm::scale(model, glm::vec3(0.050f));
        sunShader.setMat4("model", model);
        sunModel.Draw(sunShader);


        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    return 0;
}