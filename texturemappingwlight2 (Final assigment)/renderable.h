#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "SimpleVertex.h"
#include "Camera.h"

using namespace glm;
using namespace std;

class Renderable
{
private:
    GLuint vbo;
    GLuint textureId;
    int numVerts;

    vec3 position;
    vec3 rotation; 
    vec3 scale;

public:
    Renderable();
   // ~Renderable();

    // where were making the obj from the vertices array
    void createVBO(SimpleVertex vertices[], int nv);

    // then were loading it from the file
    bool loadFromOBJ(const string& filename);

    // transformation properties
    void setPosition(const vec3& pos);
    void setRotation(const vec3& rot);
    void setScale(const vec3& scale);
    void setTexture(const char* imagePath);

    // model-to-world transformation matrix
    mat4 getModelToWorldMatrix();

    // render the object
    void display(GLuint programID, const Camera& camera);
};