#include "SmallAsteroid.h"
#include "Loader.h"

std::vector<glm::vec3> SmallAsteroid::vArray;
unsigned int SmallAsteroid::vertexbuffer;
unsigned int SmallAsteroid::uvbuffer;
unsigned int SmallAsteroid::normalbuffer;
unsigned int SmallAsteroid::elementbuffer;
std::vector<unsigned short> SmallAsteroid::indices;

SmallAsteroid::SmallAsteroid()
{
}


SmallAsteroid::~SmallAsteroid()
{
}

void SmallAsteroid::LoadBuffers()
{
#if defined(PLATFORM_OSX)
	const char * modelPath = "Models/smallasteroid.obj";
#else
	const char * modelPath = "../Resources/Models/smallasteroid.obj";
#endif
	Loader::loadModel(modelPath, SmallAsteroid::vArray, SmallAsteroid::vertexbuffer, SmallAsteroid::uvbuffer, SmallAsteroid::normalbuffer, SmallAsteroid::elementbuffer, SmallAsteroid::indices);
}