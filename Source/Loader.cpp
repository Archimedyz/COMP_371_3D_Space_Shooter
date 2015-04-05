#include "Loader.h"
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"


Loader::Loader()
{
}
GLuint Loader::vertexbuffer;
GLuint Loader::uvbuffer;
GLuint Loader::normalbuffer;
GLuint Loader::elementbuffer;
std::vector<unsigned short> Loader::indices;

GLuint Loader::vertexbufferAst;
GLuint Loader::uvbufferAst;
GLuint Loader::normalbufferAst;
GLuint Loader::elementbufferAst;
std::vector<unsigned short> Loader::indicesAst;

Loader::~Loader()
{
}

void Loader::loadModelShip(const char * filePath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool res = loadOBJ(filePath, vertices, uvs, normals);

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	//load it into VBO
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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

void Loader::loadModelAsteroid(const char * filePath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	bool res = loadOBJ(filePath, vertices, uvs, normals);

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indicesAst, indexed_vertices, indexed_uvs, indexed_normals);

	//load it into VBO
	glGenBuffers(1, &vertexbufferAst);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferAst);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbufferAst);
	glBindBuffer(GL_ARRAY_BUFFER, uvbufferAst);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbufferAst);
	glBindBuffer(GL_ARRAY_BUFFER, normalbufferAst);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbufferAst);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbufferAst);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesAst.size() * sizeof(unsigned short), &indicesAst[0], GL_STATIC_DRAW);
}


