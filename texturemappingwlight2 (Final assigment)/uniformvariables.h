#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

// contains
class UniformVariables
{
private:
    GLuint programID;

public:
    // Transform uniforms
    GLuint modelToWorldTransform;
    GLuint worldToViewToProjectionTransform;

    // Lighting uniforms
    GLuint ambientLightIntensity;
    GLuint directionalLightIntensity;
    GLuint directionalLightDirection;

    // Materials 
    GLuint ka; 
    GLuint kd; 

   
    GLuint textureSampler;

    UniformVariables();
    void Init(GLuint shaderProgram);

    // Getters for uniform locations
    GLuint GetModelToWorldTransformLocation() const;
    GLuint GetWorldToViewToProjectionTransformLocation() const;
    GLuint GetAmbientLightIntensityLocation() const;
    GLuint GetDirectionalLightIntensityLocation() const;
    GLuint GetDirectionalLightDirectionLocation() const;
    GLuint GetKaLocation() const;
    GLuint GetKdLocation() const;
    GLuint GetTextureSamplerLocation() const;
};