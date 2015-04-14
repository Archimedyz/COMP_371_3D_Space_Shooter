//--------------------------------------------------------------------------------------------------------------
// Contributors
// Zackary Valenta (all)
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Particle.h"
#include <vector>

class ExplosionParticles : public Model
{
public:
	ExplosionParticles(glm::vec3 position);
	virtual ~ExplosionParticles();

	virtual void Update(float dt);
	virtual void Draw();
	void RenderShadowVolume(glm::vec4 lightPos) {}
	bool isExplosionOver() const;
	int getNumberOfParticles() const { return particles.size(); }

private:
	Particle* generateNewParticle();

	std::vector<Particle*> particles;
	static const int NUMBER_OF_EXPLOSION_PARTICLES;
};