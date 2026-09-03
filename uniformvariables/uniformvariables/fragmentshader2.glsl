#version 330

in vec4 Colour0;

out vec4 FragColor;

void main()
{
    FragColor = Colour0;
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);   //green
}