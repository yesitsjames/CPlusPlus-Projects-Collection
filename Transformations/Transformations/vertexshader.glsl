#version 330
                                       
layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Colour;

out vec4 Colour0;

uniform mat4 gTransform;
                                                                   
void main()
{   
    gl_Position = gTransform * vec4(Position.x, Position.y, Position.z, 1.0);
	Colour0 = Colour;
}