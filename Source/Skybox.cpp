// From http://learnopengl.com/code_viewer.php?code=advanced/cubemaps-exercise1


#include "Skybox.h"


Skybox::Skybox()
{
	
}

Skybox::~Skybox()
{
    
}
void Skybox::RenderSkybox()
{

}




















































//void Skybox::LoadTextures(GLuint imageFT, GLuint imageBK, GLuint imageLT, GLuint imageRT, GLuint imageUP, GLuint imageDN){
//    
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	
//}
//
//void Skybox::RenderSkybox(){
//
//    // Save Current Matrix
//    glPushMatrix();
//    
//    //Reset and transform the matrix
//    glLoadIdentity();
//    gluLookAt(
//              0,0,0,
//              0.0f, 0.0f, 0.0f,
//              0,1,0);
//    
//	//Skybox
//    glPushAttrib(GL_ENABLE_BIT);
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_COLOR_MATERIAL);
//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_LIGHTING);
//	glEnable(GL_TEXTURE_2D);
//
//	// Begin DrawSkybox
//	glColor4f(1.0, 1.0, 1.0, 1.0f);
//
//	// First apply scale matrix
//	glScalef(10, 10, 10);
//
//	float cz = -0.0f, cx = 1.0f;
//	float r = -1.0f; // If you have border issues change this to 1.005f
//	// Common Axis Z - FRONT Side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageFT);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cx, cz); glVertex3f(-r, 1.0f, -r);
//	glTexCoord2f(cx, cx); glVertex3f(-r, 1.0f, r);
//	glTexCoord2f(cz, cx); glVertex3f(r, 1.0f, r);
//	glTexCoord2f(cz, cz); glVertex3f(r, 1.0f, -r);
//	glEnd();
//
//	// Common Axis Z - BACK side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageBK);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cx, cz);  glVertex3f(-r, -1.0f, -r);
//	glTexCoord2f(cx, cx);  glVertex3f(-r, -1.0f, r);
//	glTexCoord2f(cz, cx);  glVertex3f(r, -1.0f, r);
//	glTexCoord2f(cz, cz);  glVertex3f(r, -1.0f, -r);
//	glEnd();
//
//	// Common Axis X - Left side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageLT);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cx, cx); glVertex3f(-1.0f, -r, r);
//	glTexCoord2f(cz, cx); glVertex3f(-1.0f, r, r);
//	glTexCoord2f(cz, cz); glVertex3f(-1.0f, r, -r);
//	glTexCoord2f(cx, cz); glVertex3f(-1.0f, -r, -r);
//	glEnd();
//
//	// Common Axis X - Right side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageRT);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cx, cx); glVertex3f(1.0f, -r, r);
//	glTexCoord2f(cz, cx); glVertex3f(1.0f, r, r);
//	glTexCoord2f(cz, cz); glVertex3f(1.0f, r, -r);
//	glTexCoord2f(cx, cz); glVertex3f(1.0f, -r, -r);
//	glEnd();
//
//	// Common Axis Y - Draw Up side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageUP);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cz, cz); glVertex3f(r, -r, 1.0f);
//	glTexCoord2f(cx, cz); glVertex3f(r, r, 1.0f);
//	glTexCoord2f(cx, cx); glVertex3f(-r, r, 1.0f);
//	glTexCoord2f(cz, cx); glVertex3f(-r, -r, 1.0f);
//	glEnd();
//
//	// Common Axis Y - Down side
//	glBindTexture(GL_TEXTURE_CUBE_MAP, imageDN);
//	glBegin(GL_QUADS);
//	glTexCoord2f(cz, cz);  glVertex3f(r, -r, -1.0f);
//	glTexCoord2f(cx, cz); glVertex3f(r, r, -1.0f);
//	glTexCoord2f(cx, cx); glVertex3f(-r, r, -1.0f);
//	glTexCoord2f(cz, cx); glVertex3f(-r, -r, -1.0f);
//	glEnd();
//
//	// Load Saved Matrix
//    glPopAttrib();
//	glPopMatrix();
//
//	//glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_COLOR_MATERIAL);
//	glCullFace(GL_BACK);
//
//}