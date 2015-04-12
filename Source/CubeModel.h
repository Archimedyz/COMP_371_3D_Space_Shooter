//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------


#pragma once

#include "Model.h"
#include <vector>

class CubeModel : public Model
{
public:
	CubeModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~CubeModel();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos);

private:
	// The vertex format could be different for different types of models
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
	};
	
	std::vector<glm::vec3> vertex_array;

	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;
};
