#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normals;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 Normal;
out vec3 FragPosition;

void main()
{
    Normal = Normals;
    FragPosition = vec3(model * vec4(pos,1.0f));
    gl_Position = projection * view  * vec4(FragPosition, 1.0f);
}