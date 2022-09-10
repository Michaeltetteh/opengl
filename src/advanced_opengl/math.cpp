#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


glm::vec4 blend_formula()
{
    glm::vec4 src = glm::vec4(0.0f,1.0f,0.0f,0.6f);
    glm::vec4 dest = glm::vec4(1.0f,0.0f,0.0f,1.0f);
    const float f_src = 0.6f;
    const float f_dest = 1.0 - f_src;

    //opengl blending formula
    // result = src * f_src + dest * f_dest

    glm::vec4 result = src * f_src + dest * f_dest;
    std::cout<< glm::to_string(result)<<"\n";
}

int main()
{
    blend_formula();
}

