//--------------------------------------------------------------------------------------------------------------
// Contributors
// 
// 
//--------------------------------------------------------------------------------------------------------------


#include "Model.h"
#include "Path.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include "Renderer.h"
#include "NewAsteroid.h"
#include <GL/glew.h>

using namespace std;
using namespace glm;

class AsteroidModel;

Model::Model() : Model(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f))
{
}

Model::Model(glm::vec3 position, glm::vec3 scaling) : Model(position, scaling, glm::vec3(0.0f, 0.0f, -1.0f))
{
}

Model::Model(glm::vec3 position, glm::vec3 scaling, glm::vec3 lookAt) : mName("UNNAMED"), mPosition(position),
mScaling(scaling), mYRotationAngleInDegrees(0.0f), mXRotationAngleInDegrees(0.0f), mZRotationAngleInDegrees(0.0f),
mPath(nullptr), mSpeed(0.0f), mTargetWaypoint(1), mSplineParameterT(0.0f), mCollisionRadius(1.0f),
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
	GLuint MaterialID = glGetUniformLocation(Renderer::GetShaderProgramID(), "materialCoefficients");
	glUniform4f(MaterialID, ka, kd, ks, n);
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
{
	// Remove things at center, for debugging, removes asteroids that get stuck in the middle.
//	if (glm::distance(mPosition, glm::vec3(0.0f, 0.0f, 0.0f)) < 1 && CollisionsOn)
//		mDestroyed = true;
	// Check the current model against all the rest


	for (std::vector<Model*>::iterator it = models.begin(); it < models.end(); ++it)
	{
		if ((*it) != this && CollisionsOn && (*it)->CollisionsOn) // Make sure the object isn't being compared to itself and that both objects are collidable.
		{
			if (glm::distance(mPosition, (*it)->GetPosition()) <= (mCollisionRadius + (*it)->GetCollisionRadius())) // If the distance is less than the radii combined, collide.
			{
				if (Collisions::collide_objects(this, (*it)))
				{
					if ((*it)->GetName() == "ASTEROID" && this->GetName() == "ASTEROID")
					{
							mDestroyed = true;
							(*it)->SetDestroy(true);
					}
					if ((*it)->GetName() == "PROJECTILE" && this->GetName() == "ASTEROID")
					{
						mDestroyed = true;
						(*it)->SetDestroy(true); // Set both destroyed flags to true so the collided objects are removed.
						Game::GetInstance()->AddScore(100);
					}

					if ((*it)->GetName() == "SHIP" && this->GetName() == "ASTEROID")
					{
						mDestroyed = true;
						Game::GetInstance()->GetHit();
					}
				}
			}
		}
	}
}

void Model::ActivateCollisions(bool c)
{
	CollisionsOn = c;
}

void Model::SetDestroy(bool b)
{
	mDestroyed = b;
}

// Shadow Stuff

void Model::RenderShadowVolume(glm::vec4 lightPos){

}

void Model::LoadBuffers()
{

}
