#include "Variables.h"
#include "AsteroidFactory.h"
#include "math.h"

using namespace std;

AsteroidFactory::AsteroidFactory(){}
AsteroidFactory::~AsteroidFactory(){}
AsteroidModel* AsteroidFactory::createAsteroid(){
	AsteroidModel* asteroid = new AsteroidModel();

	//Randomize these Elements
	int alpha = rand();
	int beta = rand();
	float x = cosf((float)alpha)*cosf((float)beta);
	float y = sinf(alpha);
	float z = -cosf(alpha)*sinf(beta);
	glm::vec3 initialPosition = Variables::InnerRadius*glm::normalize(glm::vec3(x, y, z)) - Variables::WorldCenter;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis = glm::vec3(x*rand(), -y*rand(), z*rand());
	float initialRotationAngle = 20.0f;
	float rotationSpeed = 40.0f;
	float speed = 1.2f * (rand() % 5);

	asteroid->SetPosition(initialPosition);
	asteroid->SetRotation(rotationAxis, initialRotationAngle);
	asteroid->SetScaling(scale);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);

	return asteroid;
}