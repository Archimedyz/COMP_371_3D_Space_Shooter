//--------------------------------------------------------------------------------------------------------------
// Contributors
// Zackary Valenta (all)
// 
//--------------------------------------------------------------------------------------------------------------

#include "ThrusterParticles.h"
#include "ShipModel.h"
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	if (particles.size() < 10)
	{
		particles.push_back(generateNewParticle());
	}

	mat4 parentWorldMatrix = parentModel->GetWorldMatrix();
	mat4 t = glm::translate(mat4(1.0f), mPosition);
	vec3 particleXAxis = glm::normalize(vec3(parentModel->GetWorldMatrix() * vec4(orientation, 0.0f)));
	vec3 particleYAxis = glm::normalize(vec3(parentModel->GetWorldMatrix() * vec4(1.0f, 0.0f, 0.0f, 0.0f)));
	vector<int> expiredParticles = vector<int>();
	
	for (int i = 0; i < particles.size(); ++i)
	{
		// if the particle is expired, delete it and erase it from the particles vector
		if (particles[i]->isExpired())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else
		{
			vec3 thrusterPosition;
			if (parentModel->GetName().compare("SHIP") == 0)
			{
				thrusterPosition = vec3(parentModel->GetWorldMatrix() * vec4(ShipModel::lowPolyShipThrusterPosition, 0.0f));
			}
			else
			{
				thrusterPosition = mPosition;
			}
			vec3 parentPosition = parentModel->GetPosition();
			float particleXMovement = particles[i]->getXMovementValue();
			float particleYMovement = particles[i]->getYMovementValue(particleXMovement);
			vec3 displacement = (particleXMovement * particleXAxis) + (particleYMovement * particleYAxis);
			//displacement = vec3(parentModel->GetWorldMatrix() * vec4(displacement, 0.0f));
			displacement = vec3(glm::rotate(mat4(1.0f), particles[i]->getRotationInDegrees1(), particleXAxis) * vec4(displacement, 0.0f));
			particles[i]->SetPosition(parentPosition + thrusterPosition + displacement);
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
	double currentTime = glfwGetTime();
	srand(currentTime * 1000);
	float randomSize = 0.025f * ((rand() % 6) + 1);		// size will be from 0.1 and 0.3
	float randomDuration = 0.5 * ((rand() % 3) + 1);	// duration will be from 0.5 and 1.5
	float randomAngle1 = (rand() % 360);				// angle will be between 0 and 359
	float randomAngle2 = (rand() % 360);				// angle will be between 0 and 359

	return new Particle(randomSize, vec3(0.06f, -0.3f, 0.1f), 1000.0f, randomAngle1, randomAngle2, randomDuration);
}
