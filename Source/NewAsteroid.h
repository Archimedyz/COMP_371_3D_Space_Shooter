//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Model.h"
#include "Texture.hpp"

class CollectionAsteroid;

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

	static void LoadBuffers();
	std::vector<glm::vec3> get_varray() { return NewAsteroid::vArray; }

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};

	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	static std::vector<glm::vec3> vArray;
	static unsigned int vertexbuffer;
	static unsigned int uvbuffer;
	static unsigned int normalbuffer;
	static unsigned int elementbuffer;
	static std::vector<unsigned short> indices;
	
	glm::vec3 direction;
	float mRotationSpeed;
	bool destroyed;
};