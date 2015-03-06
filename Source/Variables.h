#pragma once

#include <glm/common.hpp>

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