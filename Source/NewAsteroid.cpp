//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------

//Asteroid model from: https://www.filterforge.com/filters/3215.html

#include "NewAsteroid.h"
#include "Variables.h"
#include "Renderer.h"
#include <string>
#include <GL/glew.h>
#include "Loader.h"
#include "glm/ext.hpp"
#include "AsteroidFactory.h"
#include "World.h"

using namespace glm;

std::vector<glm::vec3> NewAsteroid::vArray;
unsigned int NewAsteroid::vertexbuffer;
unsigned int NewAsteroid::uvbuffer;
unsigned int NewAsteroid::normalbuffer;
unsigned int NewAsteroid::elementbuffer;
std::vector<unsigned short> NewAsteroid::indices;

GLuint mAsteroidTexture;


NewAsteroid::NewAsteroid() : Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	//initializing asteroid with lighting
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f; 

	direction = vec3(1, 1, 1);
	name = "ASTEROID";
	destroyed = false;
	mCollisionRadius = 4;
	CollisionsOn = true;
	mSpeed = 100;
	}

void NewAsteroid::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/asteroid0.obj";
#else
	const char * modelPath = "../Resources/Models/asteroid0.obj";
#endif
	Loader::loadModel(modelPath, NewAsteroid::vArray, NewAsteroid::vertexbuffer, NewAsteroid::uvbuffer, NewAsteroid::normalbuffer, NewAsteroid::elementbuffer, NewAsteroid::indices);

	mAsteroidTexture = loadBMP_custom("../Resources/Textures/AsteroidTexture.bmp");
}

NewAsteroid::~NewAsteroid()
{

}

void NewAsteroid::Update(float dt)
{
	mPosition += direction*mSpeed*dt;
	mYRotationAngleInDegrees += mRotationSpeed*dt;
}

void NewAsteroid::Draw()
{
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

	glBindTexture(GL_TEXTURE_2D, mAsteroidTexture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 3rd attribute buffer : UVs
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		3,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);


	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
		);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(3);
}

void NewAsteroid::Destroy(){
	destroyed = true;
	// perform any remining destruction actions here.
}

bool NewAsteroid::isDestroyed(){
	return destroyed;
}
void NewAsteroid::SetRotationSpeed(float rotationSpeed){
	mRotationSpeed = rotationSpeed;
}
float NewAsteroid::GetRotationSpeed(){
	return mRotationSpeed;
}
void NewAsteroid::RenderShadowVolume(glm::vec4 lightPos){}
