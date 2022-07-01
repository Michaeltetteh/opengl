#version 330 core

out vec4 FragColor;
uniform vec3 LColor;

void main()
{
    FragColor = vec4(LColor,1.0f);
}