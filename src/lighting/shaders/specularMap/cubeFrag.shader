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
};

in vec3 Normal;
in vec3 FragPosition;
in vec2 TextureCoordinate;

uniform vec3 ViewPosition;
uniform Material material;
uniform Light light;

void main()
{
    //ambient
    vec3 ambient = light.ambient * texture(material.diffuse,TextureCoordinate).rgb;

    //diffuse light calculation
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPosition);
    float diff = max(dot(norm,lightDirection),0.0f);
    vec3 diffuse = light.diffuse * (diff * texture(material.diffuse,TextureCoordinate).rgb);

    //specular lighting calculation
    vec3 viewDirection = normalize(ViewPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection,norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular =  light.specular * spec * vec3(texture(material.specular,TextureCoordinate).rgb);


    vec3 result = diffuse + ambient + specular;
    FragColor = vec4(result, 1.0f);
}