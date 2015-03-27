#include "Skybox.h"
#include "Texture.hpp"
#include <GLFW/glfw3.h>

Skybox::Skybox()
{
	
}

Skybox::~Skybox()
{
    
}

void Skybox::LoadTextures(GLuint imageBK, GLuint imageFT, GLuint imageRT, GLuint imageLT, GLuint imageUP, GLuint imageDN){
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
}

void Skybox::RenderSkybox(){

	//Skybox
	glDisable(GL_CULL_FACE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// Begin DrawSkybox
	glColor4f(1.0, 1.0, 1.0, 1.0f);

	// Save Current Matrix
	glPushMatrix();

	// Second Move the render space to the correct position (Translate)
	//glTranslatef(camera_position.GetX(), camera_position.GetY(), camera_position.GetZ());
	//glTranslatef(0,0,0);

	// First apply scale matrix
	glScalef(10, 10, 10);

	float cz = -0.0f, cx = 1.0f;
	float r = -1.0f; // If you have border issues change this to 1.005f
	// Common Axis Z - FRONT Side
	glBindTexture(GL_TEXTURE_2D, imageBK);
	glBegin(GL_QUADS);
	glTexCoord2f(cx, cz); glVertex3f(-r, 1.0f, -r);
	glTexCoord2f(cx, cx); glVertex3f(-r, 1.0f, r);
	glTexCoord2f(cz, cx); glVertex3f(r, 1.0f, r);
	glTexCoord2f(cz, cz); glVertex3f(r, 1.0f, -r);
	glEnd();

	// Common Axis Z - BACK side
	glBindTexture(GL_TEXTURE_2D, imageFT);
	glBegin(GL_QUADS);
	glTexCoord2f(cx, cz);  glVertex3f(-r, -1.0f, -r);
	glTexCoord2f(cx, cx);  glVertex3f(-r, -1.0f, r);
	glTexCoord2f(cz, cx);  glVertex3f(r, -1.0f, r);
	glTexCoord2f(cz, cz);  glVertex3f(r, -1.0f, -r);
	glEnd();

	// Common Axis X - Left side
	glBindTexture(GL_TEXTURE_2D, imageRT);
	glBegin(GL_QUADS);
	glTexCoord2f(cx, cx); glVertex3f(-1.0f, -r, r);
	glTexCoord2f(cz, cx); glVertex3f(-1.0f, r, r);
	glTexCoord2f(cz, cz); glVertex3f(-1.0f, r, -r);
	glTexCoord2f(cx, cz); glVertex3f(-1.0f, -r, -r);
	glEnd();

	// Common Axis X - Right side
	glBindTexture(GL_TEXTURE_2D, imageLT);
	glBegin(GL_QUADS);
	glTexCoord2f(cx, cx); glVertex3f(1.0f, -r, r);
	glTexCoord2f(cz, cx); glVertex3f(1.0f, r, r);
	glTexCoord2f(cz, cz); glVertex3f(1.0f, r, -r);
	glTexCoord2f(cx, cz); glVertex3f(1.0f, -r, -r);
	glEnd();

	// Common Axis Y - Draw Up side
	glBindTexture(GL_TEXTURE_2D, imageUP);
	glBegin(GL_QUADS);
	glTexCoord2f(cz, cz); glVertex3f(r, -r, 1.0f);
	glTexCoord2f(cx, cz); glVertex3f(r, r, 1.0f);
	glTexCoord2f(cx, cx); glVertex3f(-r, r, 1.0f);
	glTexCoord2f(cz, cx); glVertex3f(-r, -r, 1.0f);
	glEnd();

	// Common Axis Y - Down side
	glBindTexture(GL_TEXTURE_2D, imageDN);
	glBegin(GL_QUADS);
	glTexCoord2f(cz, cz);  glVertex3f(r, -r, -1.0f);
	glTexCoord2f(cx, cz); glVertex3f(r, r, -1.0f);
	glTexCoord2f(cx, cx); glVertex3f(-r, r, -1.0f);
	glTexCoord2f(cz, cx); glVertex3f(-r, -r, -1.0f);
	glEnd();

	// Load Saved Matrix
	glPopMatrix();

	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glCullFace(GL_BACK);
	glDisable(GL_TEXTURE_2D);

}