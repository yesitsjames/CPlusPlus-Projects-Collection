#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
private:
    vec3 position;
    vec3 target;
    vec3 up;
    
    float fieldOfView;
    float aspectRatio;
    float nearClip;
    float farClip;
    
public:
    Camera();
    Camera(const vec3& pos, const vec3& tgt, const vec3& up, 
           float fov, float aspect, float near, float far);
    
    void setPosition(const vec3& pos);
    void setTarget(const vec3& tgt);
    void setUp(const vec3& up);
    void setAspectRatio(float aspect);
    
    const vec3& getPosition() const;
    const vec3& getTarget() const;
    const vec3& getUp() const;
    
    void moveForward(float distance);
    void moveRight(float distance);
    void moveUp(float distance);
    
    void rotatePitch(float angle);
    void rotateYaw(float angle);
    
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    mat4 getViewProjectionMatrix() const;
};