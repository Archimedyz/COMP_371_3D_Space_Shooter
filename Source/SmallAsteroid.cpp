#include "SmallAsteroid.h"
#include "Loader.h"
#include "Renderer.h"

std::vector<glm::vec3> SmallAsteroid::vArray;
unsigned int SmallAsteroid::vertexbuffer;
unsigned int SmallAsteroid::uvbuffer;
unsigned int SmallAsteroid::normalbuffer;
unsigned int SmallAsteroid::elementbuffer;
std::vector<unsigned short> SmallAsteroid::indices;

SmallAsteroid::SmallAsteroid()
{
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f;

	direction = vec3(1, 1, 1);
	destroyed = false;
	mCollisionRadius = 1;
	CollisionsOn = true;
	name = "S_ASTEROID";
}


SmallAsteroid::~SmallAsteroid()
{
}

void SmallAsteroid::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/smallasteroid.obj";
#else
	const char * modelPath = "../Resources/Models/smallasteroid.obj";
#endif
	Loader::loadModel(modelPath, SmallAsteroid::vArray, SmallAsteroid::vertexbuffer, SmallAsteroid::uvbuffer, SmallAsteroid::normalbuffer, SmallAsteroid::elementbuffer, SmallAsteroid::indices);
}

void SmallAsteroid::Update(float dt)
{
	mPosition += direction*mSpeed*dt;
	mYRotationAngleInDegrees += mRotationSpeed*dt;
}

void SmallAsteroid::Draw()
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

bool SmallAsteroid::isDestroyed(){
	return destroyed;
}
void SmallAsteroid::SetRotationSpeed(float rotationSpeed){
	mRotationSpeed = rotationSpeed;
}
float SmallAsteroid::GetRotationSpeed(){
	return mRotationSpeed;
}
void SmallAsteroid::RenderShadowVolume(glm::vec4 lightPos){}
