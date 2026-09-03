#include "camera.h"

glm::mat4 getWorldToViewTransform()
{
    return glm::lookAt(
        glm::vec3(0.0f, 0.0f, 10.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // Look at target
        glm::vec3(0.0f, 1.0f, 0.0f)   // Up vector
    );
}