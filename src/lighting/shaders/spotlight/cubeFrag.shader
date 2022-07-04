#version 330 core
out vec4 FragColor;


struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    vec3 direction;
    float cutoff;
};

in vec3 Normal;
in vec3 FragPosition;
in vec2 TextureCoordinate;

uniform vec3 ViewPosition;
uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main()
{
    vec3 lightDirection = normalize(light.position - FragPosition);

    //spotlight
    float theta = dot(lightDirection,normalize(-light.direction));
    if(theta > light.cutoff)
    {
        //ambient
        vec3 ambient = light.ambient * texture(material.diffuse,TextureCoordinate).rgb;

        //diffuse light calculation
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm,lightDirection),0.0f);
        vec3 diffuse = light.diffuse * (diff * texture(material.diffuse,TextureCoordinate).rgb);

        //specular lighting calculation
        vec3 viewDirection = normalize(viewPosition - FragPosition);
        vec3 reflectDirection = reflect(-lightDirection,norm);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
        vec3 specular =  light.specular * spec * vec3(texture(material.specular,TextureCoordinate).rgb);

        //light attenuation calc
        float distance = length(light.position - FragPosition);
        float attenuation = 1.0f/ (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = diffuse + ambient + specular;
        FragColor = vec4(result, 1.0f);
    }
    else
    {
        FragColor = vec4(light.ambient * texture(material.diffuse, TextureCoordinate).rgb, 1.0);
    }

}