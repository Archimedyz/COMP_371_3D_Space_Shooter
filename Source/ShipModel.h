#pragma once
#include "Model.h"
#include "Renderer.h"
class ShipModel : public Model
{
public:
	ShipModel();
	~ShipModel();
	void Update(float dt);
	void Draw();
protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);
};

