#pragma once

#include "Particle.h"
#include <vector>

class ThrusterParticles
{
public:
	ThrusterParticles(glm::vec3 position, glm::vec3 orientation);
	virtual ~ThrusterParticles();

	void setParentModel(Model* model) { parentModel = model; }

	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos);
protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	Model* parentModel;
	glm::vec3 position;
	glm::vec3 orientation;
};