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
const float AsteroidFactory::SPEED_MAX = 15.0f;
const float AsteroidFactory::SPEED_MIN = 8.f;

AsteroidFactory::AsteroidFactory(){}
AsteroidFactory::~AsteroidFactory(){}

AsteroidModel* AsteroidFactory::createAsteroid(int type){
	AsteroidModel* asteroid = new AsteroidModel();


	//Randomize these Elements fo use later.
	float alpha = ALPHA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(ALPHA_MAX - ALPHA_MIN));
	float beta = BETA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (BETA_MAX - BETA_MIN));
	float x = cosf(alpha)*cosf(beta);
	float y = sinf(alpha);
	float z = -cosf(alpha)*sinf(beta);
	float scale_x = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_y = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_z = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float axis_x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f;
	float axis_y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f;
	float axis_z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f;
	// place asteroids on the edge of the inner sphere.
	glm::vec3 initialPosition = Variables::InnerRadius*glm::normalize(glm::vec3(x, y, z)) - Variables::WorldCenter;
	// initialize the scale.
	glm::vec3 scale = glm::vec3(scale_x, scale_y, scale_z);
	// randomize the rotation axis.
	glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));

	asteroid->SetPosition(initialPosition);
	asteroid->SetYRotation(rotationAxis, initialRotationAngle);
	asteroid->SetScaling(scale);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);

	return asteroid;
}

NewAsteroid* AsteroidFactory::createNewAsteroid(int type)
{
	NewAsteroid *asteroid = new NewAsteroid();
	srand(time(NULL));
	//Randomize these Elements fo use later.
	float alpha = ALPHA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ALPHA_MAX - ALPHA_MIN));
	float beta = BETA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (BETA_MAX - BETA_MIN));
	float x = cosf(alpha)*cosf(beta);
	float y = sinf(alpha);
	float z = -cosf(alpha)*sinf(beta);
	float scale_x = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_y = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float scale_z = SCALE_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SCALE_MAX - SCALE_MIN));
	float axis_x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	float axis_y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	float axis_z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	// place asteroids on the edge of the inner sphere.
	glm::vec3 initialPosition = Variables::InnerRadius*glm::normalize(glm::vec3(x, y, z)) - Variables::WorldCenter;
	// initialize the scale.
	glm::vec3 scale = glm::vec3(scale_x, scale_y, scale_z);
	// randomize the rotation axis.
	glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));
	speed = 10;
	asteroid->SetPosition(initialPosition);
	asteroid->SetYRotation(rotationAxis, initialRotationAngle);
	asteroid->SetScaling(scale);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);

	glm::vec3 d = glm::normalize(Variables::WorldCenter - initialPosition);
	float r = rand() % 30;
	r -= 15;
	r = r / 100;
	d.x += r;
	r = rand() % 30;
	r -= 15;

	r = r / 100;
	d.y += r;
	r = rand() % 30;
	r -= 15;

	r = r / 100;
	d.z += r;
	glm::normalize(d);
	asteroid->SetDirection(d);

	return asteroid;
}

void AsteroidFactory::RandomizeCoefficients(NewAsteroid* asteroid)
{
	float alpha = ALPHA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ALPHA_MAX - ALPHA_MIN));
	float beta = BETA_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (BETA_MAX - BETA_MIN));
	float x = cosf(alpha)*cosf(beta);
	float y = sinf(alpha);
	float z = -cosf(alpha)*sinf(beta);
	float axis_x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	float axis_y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	float axis_z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX)-0.5f;
	// place asteroids on the edge of the inner sphere.
	// initialize the scale.
	// randomize the rotation axis.
	glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));

	asteroid->SetYRotation(rotationAxis, initialRotationAngle);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);
}