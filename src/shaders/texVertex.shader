#version 330 core

layout (location=0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texture;

out vec3 ourColor;
out vec2 textureCoords;

void main()
{
    gl_Position = vec4(pos, 1.0);
    ourColor = aColor;
    textureCoords = texture;
}

