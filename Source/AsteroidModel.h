//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Model.h"
#include "Variables.h"
#include "Renderer.h"
#include <string>
#include <GL/glew.h>

class AsteroidModel : public Model
{
public:
	AsteroidModel();
	virtual ~AsteroidModel();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos);
	bool isDestroyed();
	void SetRotationSpeed(float rotationSpeed);
	float GetRotationSpeed();
	void SetHealth(int h) { health = h; }
	int GetHealth() { return health; }

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