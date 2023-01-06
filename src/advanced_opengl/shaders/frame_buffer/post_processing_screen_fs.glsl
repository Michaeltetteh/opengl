#version 330 core
out vec4 FragColor;

in vec2 TextureCoordinate;

//uniform bool inverse;
uniform sampler2D screenTexture;


//inverts screen color
vec4 invertScreenColor()
{
    return vec4(vec3(1.0 - texture(screenTexture, TextureCoordinate)), 1.0);
}

//greyscale
vec4 greyScale()
{
    FragColor = texture(screenTexture, TextureCoordinate);
    //float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;

    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;  //using weighted channels
    return vec4(average, average, average, 1.0);
}


void main()
{

//    if(inverse)
//        FragColor = invertScreenColor();
//    else
//        FragColor = vec4(texture(screenTexture, TextureCoordinate).rgb, 1.0);

    //FragColor = invertScreenColor();
    FragColor = greyScale();
}