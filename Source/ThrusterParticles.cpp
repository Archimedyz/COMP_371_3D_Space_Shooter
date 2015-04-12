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
		particles.push_back(generateNewParticle());
	}

	mat4 parentWorldMatrix = parentModel->GetWorldMatrix();
	mat4 t = glm::translate(mat4(1.0f), mPosition);
	vec3 particleXAxis = glm::normalize(orientation);
	vec3 particleYAxis = glm::normalize(parentModel->GetCamYAxis);
	vector<int> toBeDeleted = vector<int>();
	
	for (vector<Particle*>::const_iterator it = particles.begin(); it != particles.cend(); ++it)
	{
		// if the particle is expired, delete it and erase it from the particles vector
		if ((*it)->isExpired())
		{
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

Particle* generateNewParticle()
{
	srand(time(NULL));
	float randomSize = 1.0f / (rand() % 5);
	float randomDuration = (rand() % 3);
	float randomAngle = (rand() % 360);

	Particle* returnParticle = new Particle(randomSize, vec3(0.0f, 1.0f, 0.0f), 10.0f, randomAngle, randomDuration);	// TODO randomize the speed and the equation to something actually quadratic, this is linear
}
