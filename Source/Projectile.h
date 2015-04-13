//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------



#include "Model.h"

class Projectile : public Model
{
public:
	Projectile();
	Projectile(glm::vec3 origin, glm::vec3 direction);
	~Projectile();

	void Update(float);
	void Draw();

	void SetDirection(glm::vec3);
	glm::vec3 GetDirection();

	static void SetLastFired(time_t);
	static time_t GetLastFired();

	void RenderShadowVolume(glm::vec4 a);

	static void LoadBuffers();
	std::vector<glm::vec3> get_varray() { return Projectile::vArray; }

private:
	glm::vec3 mDirection;

	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	static std::vector<glm::vec3> vArray;
	static unsigned int vertexbuffer;
	static unsigned int uvbuffer;
	static unsigned int normalbuffer;
	static unsigned int elementbuffer;
	static std::vector<unsigned short> indices;

	static time_t LastFired; // Last time the player fired, to prevent an endless stream of bullets.
};