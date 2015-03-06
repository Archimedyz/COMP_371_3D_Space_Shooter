#include "BackgroundFactory.h"
#include "Variables.h"

using namespace std;

BackgroundFactory::BackgroundFactory(){};
BackgroundFactory::~BackgroundFactory(){};

BackgroundSphereModel* createBackgroundSphere()
{
	BackgroundSphereModel* backgroundSphere = new BackgroundSphereModel();
	backgroundSphere->SetPosition(Variables::WorldCenter);
	backgroundSphere->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	backgroundSphere->SetScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	backgroundSphere->SetSpeed(0.0f);
    
	return backgroundSphere;
}