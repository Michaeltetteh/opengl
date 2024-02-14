#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normals;

uniform sampler2D tex;

void main()
{
    // FragColor = texture(tex, TexCoords);
    FragColor.rgb = Normals;
    FragColor.a = 1.0f;
}