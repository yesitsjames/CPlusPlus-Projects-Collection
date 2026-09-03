#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out vec3 WorldPos;
out vec3 Normal0;
out vec2 TexCoord0;

uniform mat4 gModelToWorldTransform;
uniform mat4 gWorldToViewToProjectionTransform;

void main()
{
    // Calculate world position
    vec4 worldPosition = gModelToWorldTransform * vec4(Position, 1.0);
    WorldPos = worldPosition.xyz;
    
    // Transform normal from model space to world space
    Normal0 = mat3(gModelToWorldTransform) * Normal;
    
    // Pass through texture coordinates
    TexCoord0 = TexCoord;
    
    // Calculate final position in clip space
    gl_Position = gWorldToViewToProjectionTransform * worldPosition;
}