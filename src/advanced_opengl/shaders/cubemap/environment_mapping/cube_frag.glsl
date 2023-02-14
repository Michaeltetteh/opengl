#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

vec3 reflection()
{
    vec3 I = normalize(Position - cameraPos);
    return reflect(I, normalize(Normal));
}

vec3 refraction()
{
    float ratio = 1.00/1.52; //refractive index of air/ refractive index of glass
    vec3 I = normalize(Position - cameraPos);
    return refract(I,normalize(Normal),ratio);
}

void main()
{
    vec3 R = refraction();
    //vec3 R = reflection() + refraction();
    FragColor = vec4(texture(skybox,R).rgb,1.0);

    // if(gl_FragCoord.x < 400)
    //     FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // else
    //     FragColor = vec4(0.0, 1.0, 0.0, 1.0);

    // if(gl_FrontFacing)
    //     FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // else
    //     FragColor = vec4(0.1, 0.5, .5, 1.0);
}