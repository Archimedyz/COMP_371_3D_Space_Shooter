/*
Contributors:

Nicholas Dudek





*/

#include "Projectile.h"

time_t Projectile::LastFired = 0;

Projectile::Projectile()
{
	name = "PROJECTILE";
}

Projectile::~Projectile()
{
}

Projectile::Projectile(glm::vec3 o, glm::vec3 d)
{
	SphereModel();
	CollisionsOn = true;
	mPosition = o;
	mDirection = glm::normalize(d);
	mCollisionRadius = 2;
	mSpeed = 10;
	name = "PROJECTILE";
}

void Projectile::Update(float dt)
{
	mPosition = mPosition + (mDirection*mSpeed*dt);
}

void Projectile::SetDirection(glm::vec3 dir)
{
	mDirection = dir;
}

void Projectile::SetLastFired(time_t t)
{
	LastFired = t;
}

glm::vec3 Projectile::GetDirection()
{
	return mDirection;
}

time_t Projectile::GetLastFired()
{
	return LastFired;
}