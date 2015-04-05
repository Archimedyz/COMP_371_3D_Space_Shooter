#pragma once
#include "Model.h"
// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Loader
{
public:
	Loader();
	~Loader();
	static void loadModelShip(const char * filePath);
	static void loadModelAsteroid(const char * filePath);
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	static GLuint normalbuffer;
	static GLuint elementbuffer;
	static std::vector<unsigned short> indices;

	static GLuint vertexbufferAst;
	static GLuint uvbufferAst;
	static GLuint normalbufferAst;
	static GLuint elementbufferAst;
	static std::vector<unsigned short> indicesAst;

};

