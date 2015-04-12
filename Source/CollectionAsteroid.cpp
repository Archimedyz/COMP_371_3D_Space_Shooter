#include "CollectionAsteroid.h"
#include "NewAsteroid.h"
#include "AsteroidFactory.h"
#include "World.h"

using namespace std;
using namespace glm;

CollectionAsteroid::CollectionAsteroid() : Model()
{
	mSpeed = 1;
	CollisionsOn = true;
	mCollisionRadius = 5;
	name = "MANYASTEROIDS";
}

CollectionAsteroid::~CollectionAsteroid()
{
}

void CollectionAsteroid::Draw()
{
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Draw();
	}
}

void CollectionAsteroid::Update(float dt)
{
	mPosition += direction*mSpeed*dt;
	mYRotationAngleInDegrees += mRotationSpeed*dt;
}

void CollectionAsteroid::addChild(NewAsteroid *na)
{
	children.push_back(na);
	na->AssignParent(this);
}

void CollectionAsteroid::getDestroyed()
{
	float x, y, z;
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->SetPosition(children[i]->GetPosition() + mPosition);
		children[i]->SetDirection(mSpeed*direction + (children[i]->GetPosition() - mPosition));
		AsteroidFactory::RandomizeCoefficients(children[i]);
		children[i]->AssignParent(NULL);
		x = children[i]->GetScaling().x;
		y = children[i]->GetScaling().y;
		z = children[i]->GetScaling().z;
		children[i]->SetScaling(vec3(x/1.5, y/1.5, z/1.5));
		World::GetInstance()->AddModel(children[i]);
	}
	mDestroyed = true;
}