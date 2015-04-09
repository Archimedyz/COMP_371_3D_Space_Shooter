//From https://sidvind.com/wiki/Skybox_tutorial

#include "Skybox.h"
#include <iostream>

Skybox::Skybox()
{
	std::cout << "skybox made... \n\n";
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
	std::cout << "Unable to load BMP images on OS X... \n";
#else
	bmp_FT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_FT.bmp");
	bmp_LT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_LT.bmp");
    bmp_BK = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_BK.bmp");
    bmp_RT = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_RT.bmp");
    bmp_UP = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_UP.bmp");
    bmp_DN = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_DN.bmp");
	
#endif
    
}
void Skybox::drawSkybox()
{

	// Store the current matrix
	glPushMatrix();

	// Reset and transform the matrix.
	glLoadIdentity();
    glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	// to eliminate *white edge* effect
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	//not sure
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, bmp_FT);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, bmp_LT);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, bmp_BK);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, bmp_RT);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the up quad
	glBindTexture(GL_TEXTURE_2D, bmp_UP);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the down quad
	glBindTexture(GL_TEXTURE_2D, bmp_DN);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	// Restore enable bits and matrix
	glPopAttrib();
    glEnable(GL_DEPTH_TEST);
	glPopMatrix();
    
}



	
