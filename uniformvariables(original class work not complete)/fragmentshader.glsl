#version 330

in vec4 Colour0;
in vec3 Normal0;

out vec4 FragColor;
out vec3 FragNormal;

void main()
{
    FragNormal = Normal0;
    FragColor = Colour0;
}