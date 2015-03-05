#include "Variables.h"
#include "AsteroidFactory.h"
#include "math.h"

using namespace std;

const float AsteroidFactory::ALPHA_MAX = 90.0f;
const float AsteroidFactory::ALPHA_MIN = -90.0f;
const float AsteroidFactory::BETA_MAX = 360.0f;
const float AsteroidFactory::BETA_MIN = 0.0f;
const float AsteroidFactory::SCALE_MAX = 2.5f;
const float AsteroidFactory::SCALE_MIN = 0.5f;
const float AsteroidFactory::ROTATION_SPEED_MAX = 120.0f;
const float AsteroidFactory::ROTATION_SPEED_MIN = 40.0f;
const float AsteroidFactory::SPEED_MAX = 7.5f;
const float AsteroidFactory::SPEED_MIN = 2.5f;

AsteroidFactory::AsteroidFactory(){}
AsteroidFactory::~AsteroidFactory(){}
AsteroidModel* AsteroidFactory::createAsteroid(){
	AsteroidModel* asteroid = new AsteroidModel();

	//Randomize these Elements
	float alpha = ALPHA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(ALPHA_MAX - ALPHA_MIN));
	float beta = BETA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (BETA_MAX - BETA_MIN));
	float x = cosf(alpha)*cosf(beta);
	float y = sinf(alpha);
	float z = -cosf(alpha)*sinf(beta);
	float scale_x = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_y = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_z = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	glm::vec3 initialPosition = Variables::InnerRadius*glm::normalize(glm::vec3(x, y, z)) - Variables::WorldCenter;
	glm::vec3 scale = glm::vec3(scale_x, scale_y, scale_z);
	glm::vec3 rotationAxis = glm::vec3(x*rand(), -y*rand(), z*rand());
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));

	asteroid->SetPosition(initialPosition);
	asteroid->SetRotation(rotationAxis, initialRotationAngle);
	asteroid->SetScaling(scale);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);

	return asteroid;
}