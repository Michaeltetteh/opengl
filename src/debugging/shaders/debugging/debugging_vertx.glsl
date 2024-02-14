#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoords;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoords;
out vec3 Normals;

void main()
{
    gl_Position = projection * model * vec4(position, 1.0f);
    TexCoords = texCoords;
    Normals = aNormal;
}