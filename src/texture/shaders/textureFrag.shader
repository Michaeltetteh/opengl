#version 330 core

in vec2 textureCoords;
in vec3 ourColor;
out vec4 FragColor;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float mixFloat;
void main()
{
//    FragColor = texture(Texture,textureCoords)*vec4(ourColor,1.0f);
    FragColor = mix(texture(Texture1,textureCoords),texture(Texture2,vec2(-textureCoords.x,textureCoords.y)),mixFloat);
}