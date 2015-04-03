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

private:
	unsigned int mVertexArrayID;
	unsigned int mVertexBufferID;

	std::vector<glm::vec3> points; // first point is the head of the laser, the second is the tail
	float speed;
};

