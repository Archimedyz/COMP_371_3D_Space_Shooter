//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

// test comment ZACK!!!

#include "Model.h"
#include "Path.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;
using namespace glm;

Model::Model() : Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
}

Model::Model(glm::vec3 position, glm::vec3 scaling, glm::vec3 lookAt) : mName("UNNAMED"), mPosition(position),
mScaling(scaling), mYRotationAngleInDegrees(0.0f), mXRotationAngleInDegrees(0.0f), mZRotationAngleInDegrees(0.0f),
mPath(nullptr), mSpeed(0.0f), mTargetWaypoint(1), mSpline(nullptr), mSplineParameterT(0.0f), mCollisionRadius(1.0f),
CollisionsOn(true), mDestroyed(false),
mCamXAxis(glm::vec3(1.0f, 0.0f, 0.0f)), mCamYAxis(glm::vec3(0.0f, 1.0f, 0.0f)), mCamZAxis(glm::vec3(0.0f, 0.0f, 1.0f)),
mCameraYRotationAngleInDegrees(0.0f), mCameraXRotationAngleInDegrees(0.0f), mCameraZRotationAngleInDegrees(0.0f)
{
	mXAxis = glm::normalize(glm::cross(lookAt, vec3(0.0f, 1.0f, 0.0f)));
	mYAxis = glm::cross(mXAxis, lookAt);
	mZAxis = -lookAt;
}

Model::~Model()
{
}

void Model::Update(float dt)
{
	if (mPath != nullptr)
	{
		vec3 target = mPath->GetWaypoint(mTargetWaypoint);
		vec3 directionToTarget = target - mPosition;
		float distanceToTarget = length(directionToTarget);

		// Normalize direction and update direction
		directionToTarget = normalize(directionToTarget);
		float distance = mSpeed*dt;
		mPosition += distance * directionToTarget;

		// Update waypoint
		if (distance > distanceToTarget)
		{
			++mTargetWaypoint;
		}
	}
}

void Model::Draw()
{
}


void Model::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while (std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			//fprintf(stderr, "Error loading scene file... token:  %s!", token[0]);
			getchar();
			exit(-1);
		}
	}
}

bool Model::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty() == false)
	{
		if (token[0].empty() == false && token[0][0] == '#')
		{
			return true;
		}
		else if (token[0] == "name")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			mName = token[2];
		}
		else if (token[0] == "position")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mPosition.x = static_cast<float>(atof(token[2].c_str()));
			mPosition.y = static_cast<float>(atof(token[3].c_str()));
			mPosition.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "rotation")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mYAxis.x = static_cast<float>(atof(token[2].c_str()));
			mYAxis.y = static_cast<float>(atof(token[3].c_str()));
			mYAxis.z = static_cast<float>(atof(token[4].c_str()));
			mYRotationAngleInDegrees = static_cast<float>(atof(token[5].c_str()));

			glm::normalize(mYAxis);
		}
		else if (token[0] == "scaling")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			mScaling.x = static_cast<float>(atof(token[2].c_str()));
			mScaling.y = static_cast<float>(atof(token[3].c_str()));
			mScaling.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "pathspeed")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			float speed = static_cast<float>(atof(token[2].c_str()));
			SetSpeed(speed);
		}
		else if (token[0] == "boundpath")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			ci_string pathName = token[2];
			World* w = World::GetInstance();
			mPath = w->FindPath(pathName);

			if (mPath != nullptr)
			{
				mPosition = mPath->GetWaypoint(0);
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

glm::mat4 Model::GetWorldMatrix() const
{
	mat4 worldMatrix(1.0f);

	mat4 t = glm::translate(mat4(1.0f), mPosition);

	mat4 rx = glm::rotate(mat4(1.0f), mXRotationAngleInDegrees, mXAxis);
	mat4 ry = glm::rotate(mat4(1.0f), mYRotationAngleInDegrees, mYAxis);
	mat4 rz = glm::rotate(mat4(1.0f), mZRotationAngleInDegrees, mZAxis);

	mat4 rcx = glm::rotate(mat4(1.0f), mCameraXRotationAngleInDegrees, mCamXAxis);
	mat4 rcy = glm::rotate(mat4(1.0f), mCameraYRotationAngleInDegrees, mCamYAxis);
	mat4 rcz = glm::rotate(mat4(1.0f), mCameraZRotationAngleInDegrees, mCamZAxis);

	mat4 s = glm::scale(mat4(1.0f), mScaling);
	worldMatrix = t * rcy * rcx * rcz * ry * rx * rz * s;

	return worldMatrix;
}

void Model::SetPosition(glm::vec3 position)
{
	mPosition = position;
}

void Model::SetScaling(glm::vec3 scaling)
{
	mScaling = scaling;
}

void Model::SetXRotation(glm::vec3 axis, float angleDegrees)
{
	mXAxis = axis;
	mXRotationAngleInDegrees = angleDegrees;
}

void Model::SetYRotation(glm::vec3 axis, float angleDegrees)
{
	mYAxis = axis;
	mYRotationAngleInDegrees = angleDegrees;
}

void Model::SetZRotation(glm::vec3 axis, float angleDegrees)
{
	mZAxis = axis;
	mZRotationAngleInDegrees = angleDegrees;
}

void Model::SetCamXRotation(glm::vec3 axis, float angleDegrees)
{
	mCamXAxis = axis;
	mCameraXRotationAngleInDegrees = angleDegrees;
}

void Model::SetCamYRotation(glm::vec3 axis, float angleDegrees)
{
	mCamYAxis = axis;
	mCameraYRotationAngleInDegrees = angleDegrees;
}

void Model::SetCamZRotation(glm::vec3 axis, float angleDegrees)
{
	mCamZAxis = axis;
	mCameraZRotationAngleInDegrees = angleDegrees;
}

void Model::SetSpeed(float spd)
{
	mSpeed = spd;
}

void Model::SetCollisionRadius(float r)
{
	mCollisionRadius = r;
}

void Model::CheckCollisions(std::vector<Model*> &models)
{ 	}

void Model::ActivateCollisions(bool c)
{
	CollisionsOn = c;
}

void Model::SetDestroy(bool b)
{
	mDestroyed = b;
}