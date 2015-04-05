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
#include "Laser.h"

using namespace glm;

const float ThirdPersonCamera::SPEED_INCREASE_PERCENTAGE = 0.5f;
const float ThirdPersonCamera::SPEED_DECREASE_PERCENTAGE = 0.5f;
const float ThirdPersonCamera::MAX_ANIMATION_PITCH_ANGLE = 40.0f;
const float ThirdPersonCamera::MAX_ANIMATION_YAW_ANGLE = 40.0f;
const float ThirdPersonCamera::MAX_ANIMATION_ROLL_ANGLE = 40.0f;

ThirdPersonCamera::ThirdPersonCamera(Model* targetModel)
	: Camera(), mTargetModel(targetModel), mHorizontalAngle(0.0f), mVerticalAngle(0.0f), mRadius(10.0f),
	mModelHorizontalSensitivity(25.0f), mModelVerticalSensitivity(15.0f), mModelStandardSpeed(3.5f),
	mModelAcceration(1.0f), mModelDeceleration(-1.0f), mModelAnimationSpeed(100.0f), mModelCurrentPitch(0.0f),
	mModelCurrentYaw(0.0f), mModelCurrentRoll(0.0f)
{
	assert(mTargetModel != nullptr);
	CalculateCameraBasis();
	mModelCurrentSpeed = mModelStandardSpeed;
}

ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::CalculateCameraBasis()
{
	// Calculate Camera Vectors (LookAt, Up, Right) from Spherical Coordinates
	// Convert from Spherical to Cartesian Coordinates to get the lookAt Vector
	float x = mRadius * cosf(radians(mVerticalAngle)) * cosf(radians(mHorizontalAngle));
	float y = mRadius * sinf(radians(mVerticalAngle));
	float z = (-1) * mRadius * cosf(radians(mVerticalAngle)) * sinf(radians(mHorizontalAngle));

	mLookAt = -vec3(x, y, z);
	mLookAt = vec3(glm::rotate(mat4(1.0f), 90.0f, mTargetModel->GetYAxis()) * vec4(mLookAt.x, mLookAt.y, mLookAt.z, 0.0));
	mPosition = mTargetModel->GetPosition() - mLookAt;
	mRight = glm::normalize(glm::cross(mLookAt, vec3(0.0f, 1.0f, 0.0f)));
	mUp = glm::cross(mRight, mLookAt);
}

void ThirdPersonCamera::Update(float dt)
{
    EventManager::DisableMouseCursor();

	// ************************************************************************************************************
	// Press SPACE bar to speed up
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		// increase current model speed
		mModelCurrentSpeed += mModelAcceration * dt;
		if (mModelCurrentSpeed > (mModelStandardSpeed * (1 + SPEED_INCREASE_PERCENTAGE)))
		{
			mModelCurrentSpeed = mModelStandardSpeed * (1 + SPEED_INCREASE_PERCENTAGE);
		}
	}
	// if SPACE bar wasn't pressed and current speed is still above standard speed, then
	// reduce model back to standard speed
	else if (mModelCurrentSpeed > mModelStandardSpeed)
	{
		mModelCurrentSpeed -= mModelAcceration * dt;
		// if the above line makes the value pass the standard speed, set to standard speed
		if (mModelCurrentSpeed < mModelStandardSpeed)
		{
			mModelCurrentSpeed = mModelStandardSpeed;
		}
	}

	// ************************************************************************************************************
	// Press LEFT SHIFT to slow down
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		// decrease current model speed
		mModelCurrentSpeed += mModelDeceleration * dt;		// TODO ASK should deceleration be positive and deducted, or negative and added (done here)
		if (mModelCurrentSpeed < (mModelStandardSpeed * (1 - SPEED_INCREASE_PERCENTAGE)))
		{
			mModelCurrentSpeed = mModelStandardSpeed * (1 - SPEED_INCREASE_PERCENTAGE);
		}
	}
	// if LEFT SHIFT wasn't pressed and current speed is still below standard speed, then
	// reduce model back to standard speed
	else if (mModelCurrentSpeed < mModelStandardSpeed)
	{
		mModelCurrentSpeed -= mModelDeceleration * dt;
		// if the above line makes the value pass the standard speed, set to standard speed
		if (mModelCurrentSpeed > mModelStandardSpeed)
		{
			mModelCurrentSpeed = mModelStandardSpeed;
		}
	}

	// ************************************************************************************************************
	// Press A to turn left (decrease yaw)
	// also, make sure D is not pressed, so that if both bottons are pressed, animation state returns to normal
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) != GLFW_PRESS)
	{
		// Turn Camera Left
		mHorizontalAngle += mModelHorizontalSensitivity * dt;

		// Turn Model Left for animation
		mModelCurrentYaw += mModelAnimationSpeed * dt;
		if (mModelCurrentYaw > MAX_ANIMATION_YAW_ANGLE)
		{
			mModelCurrentYaw = MAX_ANIMATION_YAW_ANGLE;
		}

		// Roll Model Left for animation
		mModelCurrentRoll -= mModelAnimationSpeed * dt;
		if (mModelCurrentRoll < -MAX_ANIMATION_ROLL_ANGLE)
		{
			mModelCurrentRoll = -MAX_ANIMATION_ROLL_ANGLE;
		}
	}
	// if A was not pressed, move yaw and roll back to zero
	else
	{
		// if yaw is still towards left, move towards zero
		if (mModelCurrentYaw > 0.0f)
		{
			mModelCurrentYaw -= mModelAnimationSpeed * dt;
			// if the above line makes the value pass zero, set to zero
			if (mModelCurrentYaw < 0.0f)
			{
				mModelCurrentYaw = 0.0f;
			}
		}

		// if roll is still towards left, move towards zero
		if (mModelCurrentRoll < 0.0f)
		{
			mModelCurrentRoll += mModelAnimationSpeed * dt;
			// if the above line makes the value pass zero, set to zero
			if (mModelCurrentRoll > 0.0f)
			{
				mModelCurrentRoll = 0.0f;
			}
		}
	}

	// ************************************************************************************************************
	// Press D to turn right (increase yaw)
	// also, make sure D is not pressed, so that if both bottons are pressed, animation state returns to normal
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) != GLFW_PRESS)
	{
		// Turn Camera Right (increase yaw)
		mHorizontalAngle -= mModelHorizontalSensitivity * dt;

		// Turn Model Right for animation
		mModelCurrentYaw -= mModelAnimationSpeed * dt;
		if (mModelCurrentYaw < -MAX_ANIMATION_YAW_ANGLE)
		{
			mModelCurrentYaw = -MAX_ANIMATION_YAW_ANGLE;
		}

		// Roll Model Right for animation
		mModelCurrentRoll += mModelAnimationSpeed * dt;
		if (mModelCurrentRoll > MAX_ANIMATION_ROLL_ANGLE)
		{
			mModelCurrentRoll = MAX_ANIMATION_ROLL_ANGLE;
		}
	}
	// if D was not pressed, move yaw and roll back to zero
	else
	{
		// if yaw is still towards right, move towards zero
		if (mModelCurrentYaw < 0.0f)
		{
			mModelCurrentYaw += mModelAnimationSpeed * dt;
			// if the above line makes the value pass zero, set to zero
			if (mModelCurrentYaw > 0.0f)
			{
				mModelCurrentYaw = 0.0f;
			}
		}

		// if roll is towards right, move towards zero
		if (mModelCurrentRoll > 0.0f)
		{
			mModelCurrentRoll -= mModelAnimationSpeed * dt;
			// if the above line makes the value pass zero, set to zero
			if (mModelCurrentRoll < 0.0f)
			{
				mModelCurrentRoll = 0.0f;
			}
		}
	}

	// ************************************************************************************************************
	// Press W to tilt downward (decrease pitch) (inverted)
	// also, make sure S is not pressed, so that if both bottons are pressed, animation state returns to normal
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) != GLFW_PRESS)
	{
		// Tilt Camera downward
		mVerticalAngle += mModelVerticalSensitivity * dt;

		// Tilt Model downward for animation
		mModelCurrentPitch -= mModelAnimationSpeed * dt;
		if (mModelCurrentPitch < -MAX_ANIMATION_PITCH_ANGLE)
		{
			mModelCurrentPitch = -MAX_ANIMATION_PITCH_ANGLE;
		}
	}
	// if W was not pressed AND pitch is still downward, move model back to zero pitch (animation)
	else if (mModelCurrentPitch < 0.0f)
	{
		mModelCurrentPitch += mModelAnimationSpeed * dt;
		// if the above line makes the value pass zero, set to zero
		if (mModelCurrentPitch > 0.0f)
		{
			mModelCurrentPitch = 0.0f;
		}
	}

	// ************************************************************************************************************
	// Press S to tilt upward (increase pitch) (inverted)
	// also, make sure W is not pressed, so that if both bottons are pressed, animation state returns to normal
	if (glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) != GLFW_PRESS)
	{
		// Tilt Camera upward
		mVerticalAngle -= mModelVerticalSensitivity * dt;

		// Tilt Model upward for animation
		mModelCurrentPitch += mModelAnimationSpeed * dt;
		if (mModelCurrentPitch > MAX_ANIMATION_PITCH_ANGLE)
		{
			mModelCurrentPitch = MAX_ANIMATION_PITCH_ANGLE;
		}
	}
	// if S was not pressed AND pitch is still upward, move model back to zero pitch (animation)
	else if (mModelCurrentPitch > 0.0f)
	{
		mModelCurrentPitch -= mModelAnimationSpeed * dt;
		// if the above line makes the value pass zero, set to zero
		if (mModelCurrentPitch < 0.0f)
		{
			mModelCurrentPitch = 0.0f;
		}
	}

	// ************************************************************************************************************
	// Click LEFT MOUSE BUTTON to fire projectile
	vec3 currentPosition = mTargetModel->GetPosition();

	if (glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && (time(NULL)-Projectile::GetLastFired() > 0)) // Shoot, if left click and enough time has elapsed.
	{
		fireLasers();
		Projectile::SetLastFired(time(NULL)); // Set the last time fired to the current time.
	}

	// Adjust model according to changes
	vec3 modelDisplacement = glm::normalize(mLookAt) * mModelCurrentSpeed * dt;
	mTargetModel->SetPosition(currentPosition + modelDisplacement);

	mTargetModel->SetXRotation(mTargetModel->GetXAxis(), mVerticalAngle);
	mTargetModel->SetYRotation(mTargetModel->GetYAxis(), mHorizontalAngle);

	mTargetModel->SetCamXRotation(mRight, mModelCurrentPitch);
	mTargetModel->SetCamYRotation(mUp, mModelCurrentYaw);
	mTargetModel->SetCamZRotation(mLookAt, mModelCurrentRoll);

    CalculateCameraBasis();
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}

void ThirdPersonCamera::fireLasers()
{
	glm::vec3 pos = mTargetModel->GetPosition();
	glm::vec3 topRight = pos + 2.0f * normalize(mRight) + 2.0f * normalize(mUp);
	glm::vec3 topLeft = pos - 2.0f * normalize(mRight) + 2.0f * normalize(mUp);
	glm::vec3 bottomRight = pos + 2.0f * normalize(mRight) - 2.0f * normalize(mUp);
	glm::vec3 bottomLeft = pos - 2.0f * normalize(mRight) - 2.0f * normalize(mUp);

	Laser *p1 = new Laser(topRight, topRight+normalize(mLookAt));
	Laser *p2 = new Laser(bottomLeft, bottomLeft+ normalize(mLookAt));
	Laser *p3 = new Laser(bottomRight, bottomRight + normalize(mLookAt));
	Laser *p4 = new Laser(topLeft, topLeft + normalize(mLookAt));

	World::GetInstance()->AddModel(p1);
	World::GetInstance()->AddModel(p2);
	World::GetInstance()->AddModel(p3);
	World::GetInstance()->AddModel(p4);
}