//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 28/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "BSplineCamera.h"
#include "EventManager.h"
#include "World.h"
#include <GLM/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>
#include <algorithm>


using namespace glm;

BSplineCamera::BSplineCamera(BSpline* spline, float speed)
    : Camera(), mSpline(spline), mSpeed(speed), mSplineParameterT(0.0f)
{
    assert(spline != nullptr);
    mPosition = mSpline->GetPosition(mSplineParameterT);
    
    // @TODO - Use a tangent vector on the spline for the camera lookAt
	mLookAt = mSpline->GetTangent(mSplineParameterT);
	vec3 mRight = glm::cross(mLookAt, vec3(0.0f, 1.0f, 0.0f));
	mUp = glm::cross(mRight, mLookAt);
}

BSplineCamera::~BSplineCamera()
{
}

void BSplineCamera::Update(float dt)
{
    // @TODO - Using the BSpline class, update the position on the spline
    //         Set the mLookAt vector pointing in front (tangent on spline)
    //         And mUp vector being as up as possible
	// Set position along Spline.
	mPosition = mSpline->GetPosition(mSplineParameterT);
	//mLookAt = Tanget at position on Spline.
	mLookAt = mSpline->GetTangent(mSplineParameterT);
	// Calculating mUp
	vec3 mRight = glm::cross(mLookAt, vec3(0.0f, 1.0f, 0.0f));
	mUp = glm::cross(mRight, mLookAt);

	//Adjusting the ratio by which we increase parameter T, to ensure smooth animation.
	float speedRatio = mSpeed / glm::length(mLookAt);
	// We know that T repersents the seconds elapsed, so we add by dt*speedRatio.
	mSplineParameterT += speedRatio*dt;
}

glm::mat4 BSplineCamera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mLookAt, mUp);
}