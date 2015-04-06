
#include "FreeRoamCamera.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "EventManager.h"

using namespace glm;


FreeRoamCamera::FreeRoamCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 upVector)
: Camera(), mPosition(position), mLookAt(lookAt), mUpVector(upVector)
{
	mSpeed = 5.0f;
}

FreeRoamCamera::~FreeRoamCamera()
{
}

void FreeRoamCamera::Update(float dt)
{
	EventManager::DisableMouseCursor();

	//handle button events:
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		mPosition += normalize(mLookAt) * mSpeed * dt;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		mPosition -= normalize(mLookAt) * mSpeed * dt;
	} 
	if(glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		mPosition += normalize(cross(mLookAt, mUpVector)) * mSpeed * dt;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		mPosition -= normalize(cross(mLookAt, mUpVector)) * mSpeed * dt;
	} 
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		mPosition += normalize(mUpVector) * mSpeed * dt;
	}
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		mPosition -= normalize(mUpVector) * mSpeed * dt;
	}
	// handle mouse movements
	if (EventManager::GetMouseMotionX() != 0){ // horizontal
		vec3 mRight = normalize(cross(mLookAt, mUpVector));
		mLookAt += mRight * EventManager::GetMouseMotionX() * dt;
	}
	if (EventManager::GetMouseMotionY() != 0){ // vertical
		// take -Y because when the mouse goes up, the movement is negative.
		mLookAt += mUpVector * -EventManager::GetMouseMotionY() * dt;
	}

	//CalculateCameraBasis();
}


glm::mat4 FreeRoamCamera::GetViewMatrix() const
{
	return glm::lookAt(mPosition, mPosition + mLookAt, mUpVector);
}

