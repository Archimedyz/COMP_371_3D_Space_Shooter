//From https://sidvind.com/wiki/Skybox_tutorial

#include "Skybox.h"
#include "Texture.hpp"
#include "Variables.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

GLuint _skybox[6];
Skybox::Skybox()
{
	std::cout << "skybox made... ";
}

Skybox::~Skybox()
{

}

/*
 *  initSkybox
 *  ------
 *  initializes all of our textures for the skybox background
 */
void Skybox::initSkybox(void)
{ 
	//load BMP Skybox textures and make GLuints out of them
#if defined(PLATFORM_OSX)
	std::cout << "Unable to load BMP images on mac";
#else
	GLuint bmp_RT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_RT.bmp");
	GLuint bmp_LT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_LT.bmp");
	GLuint bmp_UP = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_UP.bmp");
	GLuint bmp_DN = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_DN.bmp");
	GLuint bmp_BK = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_BK.bmp");
	GLuint bmp_FT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_FT.bmp");
#endif
    
}
void Skybox::drawSkybox()
{
	// Store the current matrix
	glPushMatrix();

	// Reset and transform the matrix.
	glLoadIdentity();
	/*gluLookAt(
		0, 0, 0,
		0, 0, 0,
		0, 1, 0);*/

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	// to eliminate *white edge* effect
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, _skybox[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, _skybox[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, _skybox[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, _skybox[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, _skybox[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, _skybox[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();
}



	
