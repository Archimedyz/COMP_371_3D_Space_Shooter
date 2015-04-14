//--------------------------------------------------------------------------------------------------------------
// Contributors
// Zackary Valenta (all)
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Particle.h"
#include <vector>

class ThrusterParticles : public Model
{
public:
	ThrusterParticles(glm::vec3 position, glm::vec3 orientation);
	virtual ~ThrusterParticles();

	void setParentModel(Model* model) { parentModel = model; }
	virtual void Update(float dt);
	virtual void Draw();
	void RenderShadowVolume(glm::vec4 lightPos) {}

private:
	Particle* generateNewParticle();

	Model* parentModel;
	glm::vec3 orientation;
	std::vector<Particle*> particles;
};