#pragma once

#include "Model.h"

class NewAsteroid : public Model
{
public:
	NewAsteroid();
	virtual ~NewAsteroid();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos);
	bool isDestroyed();
	void SetRotationSpeed(float rotationSpeed);
	void SetDirection(glm::vec3 d) { direction = d; }
	glm::vec3 GetDirection() { return direction; }
	float GetRotationSpeed();
	void Destroy();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	glm::vec3 direction;

	unsigned int vertexbuffer;
	unsigned int uvbuffer;
	unsigned int normalbuffer;
	unsigned int elementbuffer;
	std::vector<unsigned short> indices;

	float mRotationSpeed;
	bool destroyed;
};