//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once
#include "Model.h"
#include "Renderer.h"
class ShipModel : public Model
{
public:
	ShipModel();
	ShipModel(glm::vec3 position, glm::vec3 scaling);
	~ShipModel();
	void Update(float dt);
	void Draw();
	void RenderShadowVolume(glm::vec4 lightPos);

	static void LoadBuffers();
	std::vector<glm::vec3> get_varray() { return ShipModel::vArray; }


	static const glm::vec3 upperLeftLaserPosition;
	static const glm::vec3 upperRightLaserPosition;
	static const glm::vec3 lowerLeftLaserPosition;
	static const glm::vec3 lowerRightLaserPosition;
	static const glm::vec3 lowPolyShipThrusterPosition;

protected:

	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	static std::vector<glm::vec3> vArray;
	static unsigned int vertexbuffer;
	static unsigned int uvbuffer;
	static unsigned int normalbuffer;
	static unsigned int elementbuffer;
	static std::vector<unsigned short> indices;
};

