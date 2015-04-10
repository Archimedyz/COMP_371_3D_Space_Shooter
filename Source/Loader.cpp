#include "Loader.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Objloader.hpp"
#include "VBOindexer.hpp"


Loader::Loader()
{
}
GLuint Loader::vertexbuffer;
GLuint Loader::uvbuffer;
GLuint Loader::normalbuffer;
GLuint Loader::elementbuffer;
std::vector<unsigned short> Loader::indices;

Loader::~Loader()
{
}

void Loader::loadModel(const char * filePath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	loadOBJ(filePath, vertices, uvs, normals);

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	//load it into VBO
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//----------------------------------------------------------------------
	// BREAKS HERE
	//----------------------------------------------------------------------
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

