/*
Contributors:

Nicholas Dudek





*/

#include "Projectile.h"
#include "Variables.h"
#include "Renderer.h"
#include <string>
// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include "Loader.h"


time_t Projectile::LastFired = 0;

Projectile::Projectile()
{
	name = "PROJECTILE";
}

Projectile::~Projectile()
{
	std::cout << "destroying projectile\n";
}

Projectile::Projectile(glm::vec3 o, glm::vec3 d)
{
	ka = 0.5f;
	kd = 0.3f;
	ks = 0.7f;
	n = 100.0f;
	CollisionsOn = true;
	mPosition = o;
	mDirection = glm::normalize(d);
	mCollisionRadius = 1;
	mSpeed = 30;
	name = "PROJECTILE";

#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/bullet.obj";
#else
	const char * modelPath = "../Resources/Models/bullet.obj";
#endif
	Loader::loadModel(modelPath, vArray, vertexbuffer, uvbuffer, normalbuffer, elementbuffer, indices);
}

void Projectile::Update(float dt)
{
	mPosition = mPosition + (mDirection*mSpeed*dt);
	if (distance(vec3(0.0f, 0.0f, 0.0f), mPosition) > 500)
		mDestroyed = true;
}

void Projectile::Draw()
{
	Model::Draw();

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

void Projectile::SetDirection(glm::vec3 dir)
{
	mDirection = dir;
}

void Projectile::SetLastFired(time_t t)
{
	LastFired = t;
}

glm::vec3 Projectile::GetDirection()
{
	return mDirection;
}

time_t Projectile::GetLastFired()
{
	return LastFired;
}

void Projectile::RenderShadowVolume(glm::vec4 a)
{

}