#version 330

in vec3 WorldPos;
in vec3 Normal0;
in vec2 TexCoord0;

out vec4 FragColor;

// Light uniforms
uniform vec3 gAmbientLightIntensity;
uniform vec3 gDirectionalLightIntensity;
uniform vec3 gDirectionalLightDirection;

// Material uniforms
uniform float gKa;  // Ambient reflection coefficient
uniform float gKd;  // Diffuse reflection coefficient

// Texture sampler
uniform sampler2D gTextureSampler;

void main()
{
    // Normalize the normal vector
    vec3 normal = normalize(Normal0);
    
    // Calculate ambient component
    vec3 ambientColor = gAmbientLightIntensity * gKa;
    
    // Calculate diffuse component
    vec3 lightDir = normalize(-gDirectionalLightDirection);
    float diffuseFactor = max(dot(normal, lightDir), 0.0);
    vec3 diffuseColor = gDirectionalLightIntensity * diffuseFactor * gKd;
    
    // Sample the texture
    vec4 textureColor = texture2D(gTextureSampler, TexCoord0);
    
    // Calculate final color
    vec3 finalColor = (ambientColor + diffuseColor) * textureColor.rgb;
    
    // Output final color
    FragColor = vec4(finalColor, 1.0);
}