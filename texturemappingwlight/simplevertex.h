#pragma once
#include <glm/glm.hpp>

struct SimpleVertex
{
    glm::vec3 pos;      // Position
    glm::vec3 normal;    // Vertex Normal
    glm::vec2 texcoord;  // Texture coordinates
};

#endif