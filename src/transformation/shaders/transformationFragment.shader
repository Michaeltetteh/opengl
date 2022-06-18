#version 330 core

out vec4 FragColor;
in vec2 textureCoords;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = mix(texture(texture1, textureCoords), texture(texture2, textureCoords), 0.2);
}