//--------------------------------------------------------------------------------------------------------------
// Contributors
// Awais Ali (Created and Implemented)
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "Camera.h"


class FreeRoamCamera : public Camera
{

public:
	FreeRoamCamera(glm::vec3 position, glm::vec3 lookAtPoint, glm::vec3 upVector);
	virtual ~FreeRoamCamera();

	virtual void Update(float dt);
	virtual glm::mat4 GetViewMatrix() const;

private:
	glm::vec3 mPosition;
	glm::vec3 mLookAt;
	glm::vec3 mUpVector;
	float mVerticalAngle;
	float mHorizontalAngle;
	float mSpeed;
};
