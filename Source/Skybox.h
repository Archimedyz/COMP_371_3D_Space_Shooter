//
// Some code taken from https://procedural.googlecode.com/svn/trunk/v1/POC/

#include <GL/glew.h>

#ifndef SKYBOX_H
#define SKYBOX_H

class Skybox{

private:
	//Textures
	GLuint imageFT;
	GLuint imageBK;
	GLuint imageLT;
	GLuint imageRT;
	GLuint imageUP;
	GLuint imageDN;

public:
	Skybox();
    ~Skybox();
	void LoadTextures(GLuint imageBK, GLuint imageFT, GLuint imageRT, GLuint imageLT, GLuint imageUP, GLuint imageDN);
	void RenderSkybox();

};

#endif