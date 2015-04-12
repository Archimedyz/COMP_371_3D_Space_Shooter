//--------------------------------------------------------------------------------------------------------------
// Contributors
// Awais Ali
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "NewAsteroid.h"
#include "Variables.h"

class AsteroidFactory{
public:
	~AsteroidFactory();
	static NewAsteroid* createNewAsteroid(int type);
	static void RandomizeCoefficients(NewAsteroid*);

private:
	AsteroidFactory();

	static const float ALPHA_MAX;
	static const float ALPHA_MIN;
	static const float BETA_MAX;
	static const float BETA_MIN;
	static const float SCALE_MAX;
	static const float SCALE_MIN;
	static const float ROTATION_SPEED_MAX;
	static const float ROTATION_SPEED_MIN;
	static const float SPEED_MAX;
	static const float SPEED_MIN;
};