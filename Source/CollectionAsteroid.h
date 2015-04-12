#pragma once

#include "Model.h"

class NewAsteroid;

class CollectionAsteroid : public Model
{
public:
	CollectionAsteroid();
	~CollectionAsteroid();

	virtual void Draw();
	virtual void Update(float);
	virtual void RenderShadowVolume(glm::vec4 lightPos) { }

	void addChild(NewAsteroid*);
	void getDestroyed();

	void setDirection(glm::vec3 v) { direction = v; }
	glm::vec3 getDirection() { return direction; }
	std::vector<NewAsteroid*> GetChildren() { return children; }
	void SetRotationSpeed(float rotationSpeed){ mRotationSpeed = rotationSpeed; }

private:
	std::vector<NewAsteroid*> children;
	float mRotationSpeed;
	glm::vec3 direction;

};

