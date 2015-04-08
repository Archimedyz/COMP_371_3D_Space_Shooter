/*
Contributors:

Nicholas Dudek





*/

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

private:
	glm::vec3 mDirection;

	static time_t LastFired; // Last time the player fired, to prevent an endless stream of bullets.
};