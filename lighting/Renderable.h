#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Renderable {
public:
    Renderable();
    virtual ~Renderable();

    virtual void Draw() const = 0;
    virtual void Update(float deltaTime) = 0;

protected:
    GLuint VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void SetupMesh();
};