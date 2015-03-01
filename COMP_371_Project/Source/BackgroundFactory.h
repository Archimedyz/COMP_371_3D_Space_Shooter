#pragma once
#include "BackgroundSphereModel.h"
#include "Renderer.h"
#include <GL/glew.h>

class BackgroundFactory
{
public:
	~BackgroundFactory();
	static BackgroundSphereModel* createBackgroundSphere;
private:
	BackgroundFactory();
};