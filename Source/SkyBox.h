//
// Some code taken from https://procedural.googlecode.com/svn/trunk/v1/POC/

#include <GL/glew.h>
#include <GL/GLU.h>
#include "Texture.hpp"
#include "Variables.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifndef SKYBOX_H
#define SKYBOX_H

class Skybox{

private:
    

public:
	Skybox();
    ~Skybox();
    void initSkybox();
    void drawSkybox();
};

#endif