#include "ThrusterParticles.h"

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>

using namespace glm;

ThrusterParticles::ThrusterParticles(float size, glm::vec3 quadraticMovement, float duration) : Model(), quadraticMovement(quadraticMovement), duration(duration)
{
	
}

ThrusterParticles::~ThrusterParticles()
{
	parentModel = NULL;
}

void Particle::Update(float dt)
{
	// If you are curious, un-comment this line to have spinning cubes!
	// That will only work if your world transform is correct...
	//mRotationAngleInDegrees += 90 * dt; // spins by 90 degrees per second

	mat4 parentWorldMatrix = parentModel->GetWorldMatrix();

}

