#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;


void main()
{
    //ambient light calculation
    float ambient_factor = 0.1f;
    vec3 ambient = ambient_factor * LightColor;

    //diffuse light calculation
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPosition - FragPosition);
    float diff = max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = diff * LightColor;

    //specular lighting calculation
    float specularFactor = 0.5f;
    vec3 viewDirection = normalize(ViewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection,norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularFactor * spec * LightColor;


    vec3 result = (diffuse + ambient + specular) * ObjectColor;
    FragColor = vec4(result, 1.0f);
}