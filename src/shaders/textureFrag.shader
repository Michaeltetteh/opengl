#version 330 core

in vec2 textureCoords;
in vec3 ourColor;
out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture,textureCoords)*vec4(ourColor,1.0f);
}