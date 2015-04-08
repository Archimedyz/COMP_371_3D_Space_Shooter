#include "NewAsteroid.h"
#include "Variables.h"
#include "Renderer.h"
#include <string>
// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include "Loader.h"
#include "glm/ext.hpp"

using namespace glm;

NewAsteroid::NewAsteroid() : Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f))
{
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f; 

	name = "ASTEROID";
	destroyed = false;
	mCollisionRadius = 4;
	CollisionsOn = true;

#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/asteroid0.obj";
#else
	const char * modelPath = "../Resources/Models/asteroid0.obj";
#endif
	Loader::loadModel(modelPath, vArray, vertexbuffer, uvbuffer, normalbuffer, elementbuffer, indices);
}

NewAsteroid::~NewAsteroid()
{
	// Free the GPU from the Vertex Buffer
//	glDeleteBuffers(1, &mVertexBufferID);
//	glDeleteVertexArrays(1, &mVertexArrayID);
}

void NewAsteroid::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	std::cout << "update\n";

	//Update posiion and rotation per frame.
	vec3 direction = Variables::WorldCenter - mPosition;
	mPosition += normalize(direction)*mSpeed*dt;

	mYRotationAngleInDegrees += mRotationSpeed*dt;
}

void NewAsteroid::Draw()
{
	GLuint WorldMatrixLocation = glGetUniformLocation(Renderer::GetShaderProgramID(), "WorldTransform");
	glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &GetWorldMatrix()[0][0]);

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

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
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


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

bool NewAsteroid::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty())
	{
		return true;
	}
	else
	{
		return Model::ParseLine(token);
	}
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