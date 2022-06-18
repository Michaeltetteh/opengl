#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

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


    return 0;
}