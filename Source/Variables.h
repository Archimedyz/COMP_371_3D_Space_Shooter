#pragma once

#ifndef VARIABLES
#define VARIABLES
#include <glm/common.hpp>


/*  Skybox Textures  */
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5


class Variables
{
public:
	static const glm::vec3 WorldCenter;
	static const float InnerRadius;
	static const float OuterRadius;

private:
	Variables();
	~Variables();
};

#endif