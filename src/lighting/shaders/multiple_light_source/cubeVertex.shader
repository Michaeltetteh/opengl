#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normals;
layout (location = 2) in vec2 textureCords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    //Normal = Normals;
    //using normal matrix
    Normal = mat3(transpose(inverse(model))) * Normals;
    FragPos = vec3(model * vec4(pos,1.0f));
    TexCoords = textureCords;
    gl_Position = projection * view  * vec4(FragPos, 1.0f);
}