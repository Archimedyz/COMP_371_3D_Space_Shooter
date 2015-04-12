#include "ThrusterParticles.h"
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;
using namespace std;

ThrusterParticles::ThrusterParticles(glm::vec3 position, glm::vec3 orientation) : Model(position, vec3(1.0f, 1.0f, 1.0f)), orientation(orientation)
{
	particles = vector<Particle*>();
}

ThrusterParticles::~ThrusterParticles()
{
	parentModel = NULL;
}

void ThrusterParticles::Update(float dt)
{
	// check if we should add particles
	// we want at most 40 particles at a time
	// if there's less than 40, add a particle per frame

	if (particles.size() < 40)
	{
		cout << particles.size() << endl;
		particles.push_back(generateNewParticle());
	}

	mat4 parentWorldMatrix = parentModel->GetWorldMatrix();
	mat4 t = glm::translate(mat4(1.0f), mPosition);
	vec3 particleXAxis = vec3(0.0f, 1.0f, 0.0f); //glm::normalize(orientation);
	vec3 particleYAxis = vec3(1.0f, 0.0f, 0.0f); //glm::normalize(parentModel->GetCamYAxis());
	
	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
	{
		// if the particle is expired, delete it and erase it from the particles vector
		if ((*it)->isExpired())
		{
			cout << "particle destroyed" << endl;
			delete *it;
			it = particles.erase(it);
		}
		else
		{
			float particleXMovement = (*it)->getXMovementValue();
			float particleYMovement = (*it)->getYMovementValue();
			vec3 displacement = (particleXMovement * particleXAxis) + (particleYMovement * particleYAxis);
			displacement = vec3(glm::rotate(mat4(1.0f), (*it)->getRotationAngleInDegrees(), particleXAxis) * vec4(displacement, 0.0f));
			(*it)->SetPosition((*it)->GetPosition() + displacement);
		}
	}
}

void ThrusterParticles::Draw()
{
	for (Particle* particle : particles)
	{
		particle->Draw();
	}
}

Particle* ThrusterParticles::generateNewParticle()
{
	srand(time(NULL));
	float randomSize = 0.1f / ((rand() % 4) + 1);		// size will be from 0.025 and 0.1
	float randomDuration = ((rand() % 2) + 1) * 1000;	// duration will be from 1 and 3
	float randomAngle = (rand() % 360);					// angle will be between 0 and 359

	return new Particle(randomSize, vec3(0.0f, 1.0f, 0.0f), 10.0f, randomAngle, randomDuration);	// TODO randomize the speed and the equation to something actually quadratic, this is linear
}
