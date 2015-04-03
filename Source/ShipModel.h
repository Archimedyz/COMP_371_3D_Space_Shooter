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
protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);
};

