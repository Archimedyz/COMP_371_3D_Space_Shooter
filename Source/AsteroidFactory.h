#pragma once

#include "AsteroidModel.h"

class AsteroidFactory{
public:
	~AsteroidFactory();
	static AsteroidModel* createAsteroid();
private:
	AsteroidFactory();
};