// From http://www.davidwparker.com/2012/12/26/opengl-screencast-video-21-skybox/


#include "Skybox.h"
#include "Texture.hpp"
#include "Variables.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>


GLuint skybox[6];
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
    
    /*
     SKY_FRONT 0
     SKY_RIGHT 1
     SKY_LEFT 2
     SKY_BACK 3
     SKY_UP 4
     SKY_DOWN 5
     */
#if defined(PLATFORM_OSX)
    skybox[SKY_FRONT] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_FT.bmp");
    skybox[SKY_RIGHT] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_RT.bmp");
    skybox[SKY_LEFT] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_LT.bmp");
    skybox[SKY_BACK] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_BK.bmp");
    skybox[SKY_UP] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_UP.bmp");
    skybox[SKY_DOWN] = loadBMP_custom("Resources/GalaxySkybox/Galaxy_DN.bmp");
#else
    skybox[SKY_FRONT] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_FT.bmp");
    skybox[SKY_RIGHT] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_RT.bmp");
    skybox[SKY_LEFT] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_LT.bmp");
    skybox[SKY_BACK] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_BK.bmp");
    skybox[SKY_UP] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_UP.bmp");
    skybox[SKY_DOWN] = loadBMP_custom("../Resources/GalaxySkybox/Galaxy_DN.bmp");
#endif
    
    
}
void Skybox::drawSkybox(double D)
{
    float white[] = {1,1,1,1};
    glColor3fv(white);
    glEnable(GL_TEXTURE_2D);
    
    /* Sides */
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
    glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
    glEnd();
    
    /* Top and Bottom */
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
    glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
    glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
    glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
    glBegin(GL_QUADS);
    glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
    glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
    glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
    glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}



	
