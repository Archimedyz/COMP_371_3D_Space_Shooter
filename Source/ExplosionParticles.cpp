//--------------------------------------------------------------------------------------------------------------
// Contributors
// Zackary Valenta (all)
// 
//--------------------------------------------------------------------------------------------------------------

#include "ExplosionParticles.h"
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace glm;
using namespace std;

const int ExplosionParticles::NUMBER_OF_EXPLOSION_PARTICLES = 100;

ExplosionParticles::ExplosionParticles(glm::vec3 position) : Model(position, vec3(1.0f, 1.0f, 1.0f))
{
	particles = vector<Particle*>();

	// create the number of particles in an explosion
	for (int i = 0; i < NUMBER_OF_EXPLOSION_PARTICLES; ++i)
	{
		particles.push_back(generateNewParticle());
	}
}

ExplosionParticles::~ExplosionParticles()
{}

// move all paticles along their quadratic trajectory
void ExplosionParticles::Update(float dt)
{
	vec3 particleXAxis = vec3(1.0f, 0.0f, 0.0f);
	vec3 particleYAxis = vec3(0.0f, 1.0f, 0.0f);
	vec3 particleZAxis = vec3(0.0f, 0.0f, 1.0f);

	for (int i = 0; i < particles.size(); ++i)
	{
		// if the particle is expired, delete it and erase it from the particles vector
		if (particles[i]->isExpired())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		// otherwise calculate its displacement and move it
		else
		{
			float particleXMovement = particles[i]->getXMovementValue();
			vec3 displacement = (particleXMovement * particleXAxis);
			mat4 yRotationMatrix = glm::rotate(mat4(1.0f), particles[i]->getRotationInDegrees1(), particleYAxis);
			mat4 zRotationMatrix = glm::rotate(mat4(1.0f), particles[i]->getRotationInDegrees2(), particleZAxis);
			displacement = vec3(zRotationMatrix * yRotationMatrix * vec4(displacement, 0.0f));
			particles[i]->SetPosition(particles[i]->GetPosition() + displacement);
		}
	}

	if (particles.size() == 0)
	{
		mDestroyed = true;
	}
}

void ExplosionParticles::Draw()
{
	for (Particle* particle : particles)
	{
		particle->Draw();
	}
}

Particle* ExplosionParticles::generateNewParticle()
{
	// randomize the values used to create the particle
	double currentTime = glfwGetTime();
	srand(currentTime * 1000);
	float randomSize = 0.1f / ((rand() % 4) + 1);		// size will be from 0.025 and 0.1
	float randomDuration = ((rand() % 3) + 1);			// duration will be from 1 and 3
	float randomAngle1 = (rand() % 360);				// angle will be between 0 and 359
	float randomAngle2 = (rand() % 360);				// angle will be between 0 and 359

	Particle* returnParticle = new Particle(randomSize, vec3(0.0f, 0.0f, 0.0f), 10.0f, randomAngle1, randomAngle2, randomDuration);	// TODO randomize the speed and the equation to something actually quadratic, this is linear

	returnParticle->ActivateCollisions(false);

	return returnParticle;
}
