//--------------------------------------------------------------------------------------------------------------
// Contributors
// Awais Ali (initial setup)
// Nicholas Dudek
//--------------------------------------------------------------------------------------------------------------
#include "AsteroidFactory.h"
#include "math.h"

using namespace std;
using namespace glm;

const float AsteroidFactory::ALPHA_MAX = 90.0f;
const float AsteroidFactory::ALPHA_MIN = -90.0f;
const float AsteroidFactory::BETA_MAX = 360.0f;
const float AsteroidFactory::BETA_MIN = 0.0f;
const float AsteroidFactory::SCALE_MAX = 1.5f;
const float AsteroidFactory::SCALE_MIN = 0.5f;
const float AsteroidFactory::ROTATION_SPEED_MAX = 120.0f;
const float AsteroidFactory::ROTATION_SPEED_MIN = 40.0f;
const float AsteroidFactory::SPEED_MAX = 15.0f;
const float AsteroidFactory::SPEED_MIN = 8.f;
const int AsteroidFactory::ASTEROID_MAX_PER_COLLECTION = 3;

AsteroidFactory::AsteroidFactory(){}
AsteroidFactory::~AsteroidFactory(){}

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

	// randomize the rotation axis.
	glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));
	speed = rand() % 4;
	asteroid->SetYRotation(rotationAxis, initialRotationAngle);
	asteroid->SetSpeed(speed);
	asteroid->SetRotationSpeed(rotationSpeed);
}

CollectionAsteroid *AsteroidFactory::createCollection()
{
	CollectionAsteroid *collection = new CollectionAsteroid();
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
	collection->SetPosition(Variables::InnerRadius*glm::normalize(glm::vec3(x, y, z)) - Variables::WorldCenter);

	glm::vec3 scale = glm::vec3(scale_x, scale_y, scale_z);
	// randomize the rotation axis.
	glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
	//randomize initial rotation angle.
	float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
	// randomized rotation speed
	float rotationSpeed = ROTATION_SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (ROTATION_SPEED_MAX - ROTATION_SPEED_MIN));
	// randomized speed
	float speed = SPEED_MIN + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (SPEED_MAX - SPEED_MIN));
	collection->SetYRotation(rotationAxis, initialRotationAngle);
	collection->SetScaling(scale);
	collection->SetSpeed(speed);
	collection->SetRotationSpeed(rotationSpeed);

	glm::vec3 d = glm::normalize(Variables::WorldCenter - collection->GetPosition());
	float r = rand() % 90;
	r -= 45;
	r = r / 100;
	d.x += r;

	r = rand() % 90;
	r -= 45;
	r = r / 100;
	d.y += r;

	r = rand() % 90;
	r -= 45;
	r = r / 100;
	d.z += r;

	glm::normalize(d);
	collection->setDirection(d);

	int asteroid_number = (rand() % ASTEROID_MAX_PER_COLLECTION) + 1;
	for (int i = 0; i < asteroid_number; ++i)
	{
		NewAsteroid *asteroid = new NewAsteroid();
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

		glm::vec3 rotationAxis = glm::vec3(axis_x, axis_y, axis_z);
		float initialRotationAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
		asteroid->SetPosition(vec3((rand() % 2) + .5, (rand() % 2) + .5, (rand() % 2) + .5));
		asteroid->SetYRotation(rotationAxis, initialRotationAngle);
		asteroid->SetScaling(scale);
		collection->addChild(asteroid);
	}

	return collection; }
