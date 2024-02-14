#include <GLFW/glfw3.h>
#include "../app/shader_g.h"
#include "../app/application.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../app/texture.h"
#include "stb_image.h"


GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

// void APIENTRY glDebugOutput(GLenum source, 
//                             GLenum type, 
//                             unsigned int id, 
//                             GLenum severity, 
//                             GLsizei length, 
//                             const char *message, 
//                             const void *userParam)
// {
//     if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

//     std::cout << "---------------" << std::endl;
//     std::cout << "Debug message (" << id << "): " <<  message << std::endl;

//     switch (source)
//     {
//         case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
//         case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
//         case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
//         case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
//         case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
//         case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
//     } std::cout << std::endl;

//     switch (type)
//     {
//         case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
//         case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
//         case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
//         case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
//         case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
//         case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
//         case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
//         case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
//         case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
//     } std::cout << std::endl;
    
//     switch (severity)
//     {
//         case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
//         case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
//         case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
//         case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
//     } std::cout << std::endl;
//     std::cout << std::endl;
// }


int main()
{ 
    Application app("Debugging opengl");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // build and compile shaders
    Shader shader("shaders/debugging/debugging_vertx.glsl", "shaders/debugging/debugging_frag.glsl");

    glCheckError();
    // configure 3D cube
    unsigned int cubeVAO, cubeVBO;
    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
        // left face
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
        // right face
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
        // bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
        // top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
    };
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0); //vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1); //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(1); //texcoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glCheckError();

    // load cube texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrComponents;
    unsigned char *data = stbi_load("resources/textures/wood.png", &width, &height, &nrComponents, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glCheckError();

    // // set up projection matrix
    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)D_WIDTH / (float)D_HEIGHT, 0.1f, 10.0f);
    // glCheckError();
    // // glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // shader.setMat4("projection", projection);
    // shader.setInt("tex", 0);
    // // glUniform1i(glGetUniformLocation(shader.getProgram(), "tex"), 0);
    // glCheckError();

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        float rotationSpeed = 10.0f;
        float angle = (float)glfwGetTime() * rotationSpeed;
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)D_WIDTH / (float)D_HEIGHT, 0.1f, 10.0f);
        model = glm::translate(model, glm::vec3(0.0, 0.0f, -2.5));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4("projection", projection);
        shader.setInt("tex", 0);
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glCheckError();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
// unsigned int quadVAO = 0;
// unsigned int quadVBO;
// void renderQuad()
// {
//     if (quadVAO == 0)
//     {
//         float quadVertices[] = {
//             // positions        // texture Coords
//             -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//             -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//              1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//              1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//         };
//         // setup plane VAO
//         glGenVertexArrays(1, &quadVAO);
//         glGenBuffers(1, &quadVBO);
//         glBindVertexArray(quadVAO);
//         glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//         glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//         glEnableVertexAttribArray(1);
//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     }
//     glBindVertexArray(quadVAO);
//     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//     glBindVertexArray(0);
// }