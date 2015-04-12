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
}

void CollectionAsteroid::addChild(NewAsteroid *na)
{
	children.push_back(na);
	na->AssignParent(this);
}

void CollectionAsteroid::getDestroyed()
{
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->SetPosition(children[i]->GetPosition() + mPosition);
		children[i]->SetDirection(direction + (children[i]->GetPosition() - mPosition));
		AsteroidFactory::RandomizeCoefficients(children[i]);
		children[i]->AssignParent(NULL);
		World::GetInstance()->AddModel(children[i]);
	}
	mDestroyed = true;
}