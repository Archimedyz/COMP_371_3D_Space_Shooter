#pragma once
#include "Model.h"
#include "Loader.h"

class AsteroidModel : public Model
{
public:
	AsteroidModel(int i);
	virtual ~AsteroidModel();
	virtual void Update(float dt);
	virtual void Draw();
	bool isDestroyed();
	void SetRotationSpeed(float rotationSpeed);
	float GetRotationSpeed();
	void Destroy();
	void SetDirection(glm::vec3 direction);
	void RandomizedDirection();

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

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	float mRotationSpeed;
	bool destroyed;
	glm::vec3 mDirection;

	// Load the texture

	// Get a handle for our "myTextureSampler" uniform
	unsigned int Texture;
	unsigned int programID;

};