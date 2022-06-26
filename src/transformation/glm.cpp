#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

int main()
{
    /**
     * vector(vec3) = (1.0f,0.0f,0.0f)
     * vector(vec4) = (1.0f,0.0f,0.0f,1.0f)
     * translation vector = (1.0f,1.0f,0.0f)
     *
     * transfromation matrix(mat4)
     * | 1.0f   0.0f  0.0f   1.0f |
     * | 0.0f   1.0f  0.0f   1.0f |
     * | 0.0f   0.0f  1.0f   0.0f |
     * | 0.0f   0.0f  0.0f   1.0f |
     *
     * translation matrix * vector(vec4)
     * | 1.0f   0.0f  0.0f   1.0f |      | 1.0f |       | 1.0f + 1.0f |   | 2.0f | x
     * | 0.0f   1.0f  0.0f   1.0f |   *  | 0.0f |   =   | 1.0f + 0.0f | = | 1.0f | y
     * | 0.0f   0.0f  1.0f   0.0f |      | 0.0f |       | 0.0f + 0.0f |   | 0.0f | z
     * | 0.0f   0.0f  0.0f   1.0f |      | 1.0f |       | 1.0f + 1.0f |   | 1.0f | w
     * */
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans(1.0f);  // identity matrix
    trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0));
    vec = trans * vec;

    std::cout<<"translated vector = "<<"("<< vec.x<<","<<vec.y<<","<<vec.z<<","<<vec.w<<")"<<"\n";
    std::cout<<glm::to_string(vec)<<"\n";

    //camera position
    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,3.0f);
    std::cout<<"Camera position = "<<glm::to_string(cameraPos)<<"\n";
    //camera direction
    glm::vec3 cameraTarget = glm::vec3(0.0f,0.0f,0.0f); //origin
    glm::vec3 cameraDirection = glm::vec3(cameraPos - cameraTarget);
    std::cout<<"Camera direction = "<<glm::to_string(cameraDirection)<<"\n";

    //Right axis
    glm::vec3 up_vec = glm::vec3(0.0f,1.0f,0.0f); //arbitrary vector
    glm::vec3 cameraRight = glm::normalize(glm::cross(up_vec,cameraDirection));
    std::cout<<"Camera Right axis "<<glm::to_string(cameraRight)<<"\n";

    //up axis
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection,cameraRight));
    std::cout<<"Camera Up axis = "<<glm::to_string(cameraUp)<<"\n";

    //lookAt matrix formula
    glm::mat4 lookat_mat = glm::mat4(
            glm::vec4(cameraRight,0),
            glm::vec4(cameraUp,0),
            glm::vec4(cameraDirection,0),
            glm::vec4(0.0f,0.0f,0.0f,1.0f)
    ) * glm::translate(glm::mat4(1.0f), -cameraPos);

    //using glm for the lookAt matrix
    glm::mat4 view;
    view = glm::lookAt(cameraPos,cameraTarget,up_vec);
    std::cout<<glm::to_string(view)<<"\n";


    /**
     * camera direction vector formula
     *
     *     d = | cos(yaw angle) *cos(pitch angle) |
     *         | sin(pitch angle)                 |
     *         | sin(yaw angle) * cos(pitch angle)|
     * */
    //yaw and pitch values are obtained from mouse/controller input
    float yaw = -90.0f;
    float pitch = 45.0f;
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

    std::cout<<"camera direction vector = "<<glm::to_string(glm::normalize(direction))<<"\n";


    //lighting
    glm::vec3 whiteLight(1.0f, 1.0f, 1.0f);
    glm::vec3 greenLight(0.0f, 1.0f, 0.0f);
    glm::vec3 redLight(1.0f, 0.0f, 0.0f);
    glm::vec3 blueLight(0.0f, 0.0f, 1.0f);

    glm::vec3 toyColor(1.0f, 0.5f, 0.31f);

    std::cout<<"\ntoyColor * whiteLight = "<<glm::to_string(whiteLight * toyColor)<<"\n";
    std::cout<<"toyColor * greenLight = "<<glm::to_string(greenLight * toyColor)<<"\n";
    std::cout<<"toyColor * redLight = "<<glm::to_string(redLight * toyColor)<<"\n";
    std::cout<<"toyColor * blueLight = "<<glm::to_string(blueLight * toyColor)<<"\n";

    return 0;
}