//--------------------------------------------------------------------------------------------------------------
// Contributors
// Nicholas Dudek
// 
//--------------------------------------------------------------------------------------------------------------



#include "ThirdPersonCamera.h"
#include "EventManager.h"
#include "World.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>
#include <algorithm>
#include "Projectile.h"

#define pi 3.14159265

using namespace glm;
using namespace std;

const float ThirdPersonCamera::SPEED_INCREASE_PERCENTAGE = 0.5f;
const float ThirdPersonCamera::SPEED_DECREASE_PERCENTAGE = 0.5f;
const float ThirdPersonCamera::MAX_ANIMATION_PITCH_ANGLE = 20.0f;
const float ThirdPersonCamera::MAX_ANIMATION_YAW_ANGLE = 25.0f;
const float ThirdPersonCamera::MAX_ANIMATION_ROLL_ANGLE = 25.0f;
const float ThirdPersonCamera::PLAYER_BOUNDING_GAME_RADIUS = 100.0f;		// 100.00f is good, this is just so controls aren't disabled until turn arround is complete
bool playerControlYaw = true;
bool playerControlPitch = true;
bool playerWasAligned = false;
const float REACTION = 75.0f;

ThirdPersonCamera::ThirdPersonCamera(Model* targetModel)
	: Camera(), mTargetModel(targetModel), mHorizontalAngle(0.0f), mVerticalAngle(0.0f), mRadius(10.0f),
	mModelHorizontalSensitivity(35.0f), mModelVerticalSensitivity(35.0f), mModelStandardSpeed(3.5f),
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
	// vec3 mTargetModelUpVector = vec3(mTargetModel->GetWorldMatrix() * vec4(0.0f, 1.0f, 0.0f, 0.0f));		// the camera up is moving with the model up so it rotates with it, but since mRight and mLookAt stay the same, yaw and pitch stay the same. Good for first erson camera
	vec3 mTargetModelUpVector = vec3(glm::rotate(mat4(1.0f), mTargetModel->GetYRotationAngle(), mTargetModel->GetXAxis()) * vec4(0.0f, 1.0f, 0.0f, 0.0f));
	vec3 calcVector = (isUpBetween90and270()) ? vec3(0.0f, -1.0f, 0.0f) : vec3(0.0f, 1.0f, 0.0f);		// use world up when right side up, otherwise use opposite of world up
	mRight = glm::normalize(glm::cross(mLookAt, calcVector));
	mUp = glm::cross(mRight, mLookAt);
}

void ThirdPersonCamera::Update(float dt)
{
    EventManager::DisableMouseCursor();

	bool space = false;
	bool shift = false;
	bool a = false;
	bool d = false;
	bool w = false;
	bool s = false;
	bool mouseLeft = false;

	vec3 mModelLookAt = glm::normalize(vec3(mTargetModel->GetWorldMatrix() * vec4(0.0f, 0.0f, 1.0f, 0.0f)));
	vec3 modelToCenter = -(mTargetModel->GetPosition());

	vector<float> deviationFromCenter = getVHAnglesBetweenVectors(mLookAt, modelToCenter);

	cout << "V: " << deviationFromCenter.at(0) << "    H: " << deviationFromCenter.at(1) << "     distance: " << length(mTargetModel->GetPosition() - vec3(0.0f, 0.0f, 0.0f)) << "    " << playerControlPitch << "   " << playerControlYaw << endl;		// shows calculated V and H deviations on console

	if (!isTargetModelOutOfBounds() && playerControlYaw && playerControlPitch)
	{
		playerWasAligned = false;
		space = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS;
		shift = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		a = ((isUpBetween90and270()) ? glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS : glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS);
		d = ((isUpBetween90and270()) ? glfwGetKey(EventManager::GetWindow(), GLFW_KEY_A) == GLFW_PRESS : glfwGetKey(EventManager::GetWindow(), GLFW_KEY_D) == GLFW_PRESS);
		w = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_W) == GLFW_PRESS;
		s = glfwGetKey(EventManager::GetWindow(), GLFW_KEY_S) == GLFW_PRESS;
		mouseLeft = glfwGetMouseButton(EventManager::GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	}
	else
	{
		if (isTargetModelOutOfBounds() && !playerWasAligned && playerControlPitch && playerControlYaw)	// only remove controls if player is out of bounds, was not aligned and has full control
		{
			playerControlYaw = false;
			playerControlPitch = false;
		}

		// slow down
		shift = true;
		if (deviationFromCenter.at(0) > 0.01f && !playerControlPitch)
		{
			s = true;
		}
		else if (deviationFromCenter.at(1) > 0.01f && !playerControlYaw)
		{
			if (isUpBetween90and270())
			{
				a = true;
			}
			else
			{
				d = true;
			}
		}
		if (deviationFromCenter.at(0) < 0.01f)
		{
			playerControlPitch = true;
		}
		if (deviationFromCenter.at(1) < 0.01f)
		{
			playerControlYaw = true;
		}
		if (playerControlPitch && playerControlYaw)
		{
			playerWasAligned = true;
		}
	}

	TranslateControls(dt, space, shift, a, d, w, s, mouseLeft);
	
	// cout << length(mTargetModel->GetPosition() - vec3(0.0f, 0.0f, 0.0f)) << endl;		// shows distance from (0,0,0) on console

	// Adjust model according to changes
	vec3 modelDisplacement = mModelLookAt * mModelCurrentSpeed * dt;
	mTargetModel->SetPosition(mTargetModel->GetPosition() + modelDisplacement);

	mTargetModel->SetXRotation(mTargetModel->GetXAxis(), mVerticalAngle);
	mTargetModel->SetYRotation(mTargetModel->GetYAxis(), mHorizontalAngle);

	mTargetModel->SetCamXRotation(mRight, mModelCurrentPitch);
	mTargetModel->SetCamYRotation(mUp, mModelCurrentYaw * ((isUpBetween90and270()) ? (-1) : 1));		// invert the yaw animation when upside down
	mTargetModel->SetCamZRotation(mLookAt, mModelCurrentRoll * ((isUpBetween90and270()) ? (-1) : 1));	// invert the roll animation when upside down

    CalculateCameraBasis();
}

void ThirdPersonCamera::TranslateControls(float dt, bool space, bool shift, bool a, bool d, bool w, bool s, bool mouseLeft)
{
	// ************************************************************************************************************
	// Press SPACE bar to speed up
	if (space)
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
	if (shift)
	{
		// decrease current model speed
		mModelCurrentSpeed += mModelDeceleration * dt;
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
	if (a && !d)
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
	if (d && !a)
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
	if (w && !s)
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
	if ( s &&  !w)
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

	if (mouseLeft && (time(NULL) - Projectile::GetLastFired() > 0))	// Shoot, if left click and enough time has elapsed.
	{
		Projectile *proj = new Projectile(mTargetModel->GetPosition(), mLookAt);
		proj->SetXRotation(mTargetModel->GetXAxis(), mVerticalAngle);
		proj->SetYRotation(mTargetModel->GetYAxis(), mHorizontalAngle);

		World::GetInstance()->AddModel(proj);
		Projectile::SetLastFired(time(NULL)); // Set the last time fired to the current time.
	}
}

bool ThirdPersonCamera::isUpBetween90and270() const
{
	float mModedVerticalAngle = fmod(abs(mVerticalAngle), 360); // * ((mVerticalAngle >= 0) ? 1 : (-1));		// moded angle with sign
	return (mModedVerticalAngle >= 90 && mModedVerticalAngle <= 270);
}

bool ThirdPersonCamera::isTargetModelOutOfBounds() const
{
	return (length(mTargetModel->GetPosition() - vec3(0.0f, 0.0f, 0.0f)) > PLAYER_BOUNDING_GAME_RADIUS);
}

vector<float> ThirdPersonCamera::getVHAnglesBetweenVectors(vec3 vector1, vec3 vector2) const
{
	vector<float> returnVector = vector<float>();

	// calculate vertical angle
	vec3 vector1YZ = vec3(0.0f, vector1.y, vector1.z);
	vec3 vector2YZ = vec3(0.0f, vector2.y, vector2.z);
	float magnitude1YZ = length(vector1YZ);
	float magnitude2YZ = length(vector2YZ);
	float verticalAngle = acosf(glm::dot(vector1YZ, vector2YZ) / (magnitude1YZ * magnitude2YZ));
	returnVector.push_back(verticalAngle);

	// claculate horizontal angle
	vec3 vector1XZ = vec3(vector1.x, 0.0f, vector1.z);
	vec3 vector2XZ = vec3(vector2.x, 0.0f, vector2.z);
	float magnitude1XZ = length(vector1XZ);
	float magnitude2XZ = length(vector2XZ);
	float horizontalAngle = acosf(glm::dot(vector1XZ, vector2XZ) / (magnitude1XZ * magnitude2XZ));
	returnVector.push_back(horizontalAngle);

	// cout << "vertical: " << glm::dot(vector1YZ, vector2YZ) / (magnitude1YZ * magnitude2YZ) << "		horizontal: " << glm::dot(vector1XZ, vector2XZ) / (magnitude1XZ * magnitude2XZ) << endl;

	return returnVector;
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}
