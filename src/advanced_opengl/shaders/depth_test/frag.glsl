#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinate;

uniform sampler2D texture1;

float near = 0.1f;
float far = 100.0f;

float linearizedDepth(float depth)
{
    float ndc_z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - ndc_z * (far - near));
}

void main()
{
    //FragColor = texture(texture1, TextureCoordinate);
    //FragColor = vec4(vec3(gl_FragCoord.z),1.0f);
    float depth = linearizedDepth(gl_FragCoord.z) / far;
    FragColor = vec4(vec3(depth),1.0f);

}
