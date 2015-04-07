/*
Contributors:

Nicholas Dudek





*/

#include "ParsingHelper.h"
#include "Model.h"
#include <vector>

#include <GLM/glm.hpp>

class Laser :
	public Model
{
public:
	Laser();
	Laser(glm::vec3, glm::vec3);
	~Laser();

	void CreateVertexBuffer();

	virtual void Update(float dt);
	virtual void Draw();
	virtual void RenderShadowVolume(glm::vec4 lightPos){}

private:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 color;
	};
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	std::vector<glm::vec3> points; // first point is the head of the laser, the second is the tail
	float speed;
};

// spent like 2h30