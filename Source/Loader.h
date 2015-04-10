#pragma once
#include "Model.h"
#include "Renderer.h"
#include "Texture.hpp"
#include "Objloader.hpp"
#include "VBOindexer.hpp"
// Include GLEW
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
	static void loadModel(const char * filePath);
	static GLuint vertexbuffer;
	static GLuint uvbuffer;
	static GLuint normalbuffer;
	static GLuint elementbuffer;
	static std::vector<unsigned short> indices;
};

