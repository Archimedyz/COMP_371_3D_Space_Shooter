//
// Some code taken from https://procedural.googlecode.com/svn/trunk/v1/POC/

#include <GL/glew.h>
#include "Texture.hpp"
#include "Variables.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef SKYBOX_H
#define SKYBOX_H

class Skybox{

public:
	Skybox();
    ~Skybox();
    void initSkybox();
    void drawSkybox();
    
private:
    GLuint bmp_FT;
    GLuint bmp_LT;
    GLuint bmp_BK;
    GLuint bmp_RT;
    GLuint bmp_UP;
    GLuint bmp_DN;
};

#endif