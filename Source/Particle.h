//--------------------------------------------------------------------------------------------------------------
// Contributors
// Zackary Valenta (all)
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Model.h"
#include <vector>

class Particle : public Model
{
public:
	Particle(float size, glm::vec3 quadraticMovement, float speed, float roatationInDegrees1, float roatationInDegrees2, float duration);
	virtual ~Particle();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos);
	bool isExpired() const;
	float getXMovementValue();
	float getYMovementValue(double xMovement);
	float getRotationInDegrees1() { return randomRotationInDegrees1; }
	float getRotationInDegrees2() { return randomRotationInDegrees2; }

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	// particle attributes
	glm::vec3 quadraticMovement;
	float speed;
	float randomRotationInDegrees1;
	float randomRotationInDegrees2;
	double startTime;
	float duration;

	std::vector<glm::vec3> vertex_array;

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};
