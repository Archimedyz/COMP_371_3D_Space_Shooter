//--------------------------------------------------------------------------------------------------------------
// Contributors
// Awais Ali
// 
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include <glm/common.hpp>
#include "fmod/fmod.h"

class Variables
{
public:
	static const glm::vec3 WorldCenter;
	static const float InnerRadius;
	static const float OuterRadius;
    static FMOD_SYSTEM * fmodsystem;

private:
	Variables();
	~Variables();
};