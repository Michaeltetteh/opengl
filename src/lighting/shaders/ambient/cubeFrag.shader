#version 330 core

out vec4 FragColor;
//uniform vec3 Color;
uniform vec3 ObjectColor;
uniform vec3 LightColor;

void main()
{
    float ambient_factor = 0.1f;
    vec3 n_light_color = ambient_factor * LightColor;
    vec3 ambiet_light = n_light_color * ObjectColor;

    FragColor = vec4(ambiet_light, 1.0f);
}