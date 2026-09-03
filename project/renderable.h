#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

using namespace glm;

class Renderable
{
private:
	GLuint vbo;
	int numverts;

public:
	// Initalise data members only
	Renderable();

	// Create our renderable
	void createVbo(vec3 vertices[], int nv);

	// Render our object
	void render();

	 
};

