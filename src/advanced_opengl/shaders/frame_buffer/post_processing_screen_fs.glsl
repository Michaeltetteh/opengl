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

//kernel effects
vec4 kernel()
{
    const float offset = 1.0 / 300.0;
    
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    // sharpen kernel
    //float kernel[9] = float[](
    //    -1, -1, -1,
    //    -1, 9 , -1,
    //    -1, -1, -1
    //);


    // Edge detection kernel
    float kernel[9] = float[](
        1,  1,   1,
        1,  -8,  1,
        1,  1,   1
    );

    //blur kernel
    //float kernel[9] = float[](
    //     1.0 / 16, 2.0 / 16, 1.0 / 16,
    //     2.0 / 16, 4.0 / 16, 2.0 / 16,
    //     1.0 / 16, 2.0 / 16, 1.0 / 16
    //);


    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TextureCoordinate.xy + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    return vec4(col, 1.0);
}

void main()
{

//    if(inverse)
//        FragColor = invertScreenColor();
//    else
//        FragColor = vec4(texture(screenTexture, TextureCoordinate).rgb, 1.0);

    //FragColor = invertScreenColor();
    //FragColor = greyScale();
    FragColor = kernel();
}