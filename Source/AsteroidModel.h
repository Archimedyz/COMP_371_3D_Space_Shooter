#pragma once

#include "Model.h"

class AsteroidModel : public Model
{
public:
	AsteroidModel();
	virtual ~AsteroidModel();
	virtual void Update(float dt);
	virtual void Draw();
	bool isDestroyed();
	void SetRotationSpeed(float rotationSpeed);
	float GetRotationSpeed();

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

private:
	void Destroy();
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	int health;
	float mRotationSpeed;
	bool destroyed;
};