#include "renderable.h"
#include "simplevertex.h"
#include "uniformvariables.h"
#include "camera.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <Windows.h>

GLuint VBO;
int NUMVERTS = 0;
GLuint gTextureObject;

void createVertexBuffer()
{
    // Create some vertices to put in our VBO.
    // Create vertex buffer
    NUMVERTS = 24;
    SimpleVertex vertices[] =
    {
        // Side 1 Front
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        {glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        {glm::vec3(1.0f,-1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        {glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},

        // ... [rest of the vertex data]
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * NUMVERTS, vertices, GL_STATIC_DRAW);
}

void initLights()
{
    // Setup the ambient light
    glm::vec3 ambientLightIntensity = glm::vec3(0.1f, 0.1f, 0.1f);
    glUniform3fv(gAmbientLightIntensityLoc, 1, &ambientLightIntensity[0]);

    // Setup the directional light
    glm::vec3 directionalLightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    normalize(directionalLightDirection);
    glUniform3fv(gDirectionalLightDirectionLoc, 1, &directionalLightDirection[0]);
    glm::vec3 directionalLightIntensity = glm::vec3(0.8f, 0.8f, 0.8f);
    glUniform3fv(gDirectionalLightIntensityLoc, 1, &directionalLightIntensity[0]);
}

void initTexture(const char* imagepath)
{
    // ... [texture initialization code]
}

void renderSceneCallBack()
{
    // Clear the back buffer and the z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get view transform from camera
    glm::mat4 worldToViewTransform = getWorldToViewTransform();

    // Create projection transform
    glm::mat4 projectionTransform = glm::perspective(45.0f, (float)1024 / (float)768, 1.0f, 100.0f);

    // Combine transforms
    glm::mat4 worldToViewToProjectionTransform = projectionTransform * worldToViewTransform;

    // Update the transforms in the shader
    glUniformMatrix4fv(gWorldToViewToProjectionTransformLoc, 1, GL_FALSE, &worldToViewToProjectionTransform[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (const GLvoid*)24);

    // Set material properties
    glUniform1f(gKaLoc, 0.2f);
    glUniform1f(gKdLoc, 0.8f);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureObject);
    glUniform1i(gTextureSamplerLoc, 0);

    // Draw triangle
    glm::mat4 modelToWorldTransform = glm::mat4(1.0f);
    static float angle = 0.0f;
    angle += 1.0f;
    modelToWorldTransform = glm::rotate(modelToWorldTransform, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(gModelToWorldTransformLoc, 1, GL_FALSE, &modelToWorldTransform[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glutSwapBuffers();
}

void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
}