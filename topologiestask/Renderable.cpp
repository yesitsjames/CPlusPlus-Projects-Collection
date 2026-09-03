#pragma once
#include "Renderable.h"

Renderable::Renderable() 
{
	vbo = 0;
	numverts = 0;
}

void Renderable::createVbo(vec3 vertices[], int nv)
{
	numverts = nv;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numverts, vertices, GL_STATIC_DRAW);
}

void Renderable::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(GL_TRIANGLES, 0, numverts);
}