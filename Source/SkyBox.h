//
// Some code taken from https://procedural.googlecode.com/svn/trunk/v1/POC/

#include <GL/glew.h>

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