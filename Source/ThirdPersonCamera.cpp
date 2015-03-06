//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 28/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include "World.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>
#include <algorithm>

#define pi 3.14159265

#include "Projectile.h"

using namespace glm;


ThirdPersonCamera::ThirdPersonCamera(Model* targetModel)
    : Camera(), mTargetModel(targetModel), mHorizontalAngle(0.0f), mVerticalAngle(0.0f), mRadius(10.0f)

{
    assert(mTargetModel != nullptr);
    CalculateCameraBasis();
	mSpeed = 1.0;
	mRadius = 10.0;
}

ThirdPersonCamera::~ThirdPersonCamera()
{
	mSpeed = 1.0;
	mRadius = 10.0;
}

void ThirdPersonCamera::CalculateCameraBasis()
{
	// @TODO
    // Calculate Camera Vectors (LookAt, Up, Right) from Spherical Coordinates
    // Convert from Spherical to Cartesian Coordinates to get the lookAt Vector
	mLookAt = vec3(glm::sin(mHorizontalAngle * pi / 180), glm::sin(mVerticalAngle * pi / 180), -glm::cos(mHorizontalAngle*pi / 180));
	mRight = vec3(glm::cos(mHorizontalAngle * pi/180), 0.0f, glm::sin(mHorizontalAngle*pi/180));
	mUp = glm::cross(mRight, mLookAt); //vec3(glm::sin(mHorizontalAngle * pi / 180), glm::cos(mVerticalAngle * pi / 180), -glm::sin(mVerticalAngle*pi / 180)* glm::cos(mHorizontalAngle*pi / 180));
	// Easier to calculate the three camera vectors, and then just position the camera to -10*lookAt
	mPosition = mTargetModel->GetPosition() - mRadius * mLookAt;
}

void ThirdPersonCamera::Update(float dt)
{
    EventManager::DisableMouseCursor();
	// @TODO
    // 1 - Map Mouse motion to Spherical Angles
	if (EventManager::GetMouseMotionX() != 0){
		// rotate horizontal
		mHorizontalAngle += glm::atan(EventManager::GetMouseMotionX()/mRadius);
		// 3 - Wrap Horizontal angle within [-180, 180] degrees

		// rotate model
		mTargetModel->SetRotation(vec3(0.0f, 1.0f, 0.0f), -mHorizontalAngle);
	}
	if (EventManager::GetMouseMotionY() != 0){
		// rotate Verticle
		// < 0 mouse moves up. -> look down
		// > 0 mouse moves down. -> look up
		mVerticalAngle -= glm::atan(EventManager::GetMouseMotionY()/mRadius);
    // 2 - Clamp vertical angle to [-85, 0] degrees
	}

 
    
	glm::vec3 currPosition = mTargetModel->GetPosition();
	glm::vec3 forwardDirection = vec3(mRight.z, 0.0f, -mRight.x);
    // Press W to move Forward
    if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W ) == GLFW_PRESS) // Move forwards
    {
		mTargetModel->SetPosition(currPosition + forwardDirection * (mSpeed*dt));
    }
	else if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS) // Move backwards
	{
		mTargetModel->SetPosition(currPosition - forwardDirection * (mSpeed*dt));
	}
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS) // Move left
	{
		mTargetModel->SetPosition(currPosition - mRight * (mSpeed*dt));
	}
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS) // Move right
	{
		mTargetModel->SetPosition(currPosition + mRight * (mSpeed*dt));
	}
	if (glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && (time(NULL)-Projectile::GetLastFired() > 0)) // Shoot, if left click and enough time has elapsed.
	{
		Projectile *p = new Projectile(currPosition+mLookAt+mLookAt+mLookAt, mLookAt); // Start position should be determined differently probably.
		World::GetInstance()->AddModel(p);
		Projectile::SetLastFired(time(NULL)); // Set the last time fired to the current time.
	}
    
    CalculateCameraBasis();
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}
