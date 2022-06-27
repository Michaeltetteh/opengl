#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPosition;



void main()
{
    //ambient light calculation
    float ambient_factor = 0.1f;
    vec3 ambient = ambient_factor * LightColor;
    //vec3 ambiet_light = n_light_color * ObjectColor;

    //diffuse light calculation
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPosition - FragPosition);
    float diff = max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = diff * LightColor;

    vec3 result = (diffuse + ambient) * ObjectColor;
    FragColor = vec4(result, 1.0f);
}