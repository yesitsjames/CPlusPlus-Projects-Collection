#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera() :
    position(0.0f, 0.0f, 10.0f),
    target(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    fieldOfView(45.0f),
    aspectRatio(4.0f / 3.0f),
    nearClip(1.0f),
    farClip(100.0f)
{
}

Camera::Camera(const vec3& pos, const vec3& tgt, const vec3& up,
    float fov, float aspect, float near, float far) :
    position(pos),
    target(tgt),
    up(up),
    fieldOfView(fov),
    aspectRatio(aspect),
    nearClip(near),
    farClip(far)
{
}


//camera set up, allocating position, targets, 


void Camera::setPosition(const vec3& pos) {
    position = pos;
}

void Camera::setTarget(const vec3& tgt) {
    target = tgt;
}

void Camera::setUp(const vec3& upVec) {
    up = upVec;
}

void Camera::setAspectRatio(float aspect) {
    aspectRatio = aspect;
}

const vec3& Camera::getPosition() const {
    return position;
}

const vec3& Camera::getTarget() const {
    return target;
}

const vec3& Camera::getUp() const {
    return up;
}

void Camera::moveForward(float distance) {
    vec3 direction = normalize(target - position);
    position += direction * distance;
    target += direction * distance;
}

void Camera::moveRight(float distance) {
    vec3 direction = normalize(target - position);
    vec3 right = normalize(cross(direction, up));
    position += right * distance;
    target += right * distance;
}

void Camera::moveUp(float distance) {
    position += up * distance;
    target += up * distance;
}

void Camera::rotatePitch(float angle) {
    vec3 direction = target - position;
    vec3 right = normalize(cross(direction, up));
    vec3 newDirection = rotate(direction, angle, right);
    target = position + newDirection;
}

void Camera::rotateYaw(float angle) {
    vec3 direction = target - position;
    vec3 newDirection = rotate(direction, angle, up);
    target = position + newDirection;
}

mat4 Camera::getViewMatrix() const {
    return lookAt(position, target, up);
}

mat4 Camera::getProjectionMatrix() const {
    return perspective(radians(fieldOfView), aspectRatio, nearClip, farClip);
}

mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}