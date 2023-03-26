#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices=5) out;

//color interface block
in VS_OUT
{
    vec3 color;
} gs_in[];

//pass color to fragment shader
out vec3 fColor;

void draw_house(vec4 position)
{
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left
    EmitVertex();
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0);  // 3:top-left
    EmitVertex();
    gl_Position = position + vec4( 0.2, 0.2, 0.0, 0.0);  // 4:top-right
    EmitVertex();
    gl_Position = position + vec4( 0.0, 0.4, 0.0, 0.0);  // 5:top
    fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();
    
    EndPrimitive();
}


void main()
{
    fColor = gs_in[0].color;
    draw_house(gl_in[0].gl_Position);
}