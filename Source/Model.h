//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once 

#include "ParsingHelper.h"

#include <vector>
#include <string>
#include <GLM/glm.hpp>
#include "Game.h"
#include "Collisions.h"

class Path;
class BSpline;

class Model
{
public:
	Model();
	Model(glm::vec3 position, glm::vec3 scaling);
	Model(glm::vec3 position, glm::vec3 scaling, glm::vec3 lookAt);
	virtual ~Model();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void RenderShadowVolume(glm::vec4 lightPos) = 0;

	void CheckCollisions(std::vector<Model*> &m);

	void Load(ci_istringstream& iss);

	virtual glm::mat4 GetWorldMatrix() const;

	void SetPosition(glm::vec3 position);
	void SetScaling(glm::vec3 scaling);
	void SetXRotation(glm::vec3 axis, float angleDegrees);
	void SetYRotation(glm::vec3 axis, float angleDegrees);
	void SetZRotation(glm::vec3 axis, float angleDegrees);
	void SetCamXRotation(glm::vec3 axis, float angleDegrees);
	void SetCamYRotation(glm::vec3 axis, float angleDegrees);
	void SetCamZRotation(glm::vec3 axis, float angleDegrees);
	void SetCollisionRadius(float r);
	void SetDestroy(bool);

	void ActivateCollisions(bool); // For debugging probably

	glm::vec3 GetPosition() const		{ return mPosition; }
	glm::vec3 GetScaling() const		{ return mScaling; }
	glm::vec3 GetXAxis() const			{ return mXAxis; }
	glm::vec3 GetYAxis() const			{ return mYAxis; }
	glm::vec3 GetZAxis() const			{ return mZAxis; }
	float     GetXRotationAngle() const	{ return mXRotationAngleInDegrees; }
	float     GetYRotationAngle() const	{ return mYRotationAngleInDegrees; }
	float     GetZRotationAngle() const	{ return mZRotationAngleInDegrees; }
	float GetCollisionRadius() const	{ return mCollisionRadius; }
	bool IsDestroyed() const			{ return mDestroyed; }
    std::string GetName()                 { return name; }
	ci_string GetCIName()                 { return mName; }
	virtual std::vector<glm::vec3> get_varray() { return vArray; }

    void SetSpeed(float spd);
	bool CollisionsOn; // For debugging probably

	// must be called in setup once before any members of the class are instantiated. loads the drawing buffers. overload it with the appropriate filename.
	static void LoadBuffers();

	// SHADOW STUFF
	struct surface{};

protected:
	virtual bool ParseLine(const std::vector<ci_string> &token);

	std::string name;
	ci_string mName; // The model name is mainly for debugging
	glm::vec3 mPosition;
	glm::vec3 mScaling;
	float     mXRotationAngleInDegrees;
	float     mYRotationAngleInDegrees;
	float     mZRotationAngleInDegrees;
	glm::vec3 mYAxis;
	glm::vec3 mXAxis;
	glm::vec3 mZAxis;
	float     mCameraXRotationAngleInDegrees;
	float     mCameraYRotationAngleInDegrees;
	float     mCameraZRotationAngleInDegrees;
	glm::vec3 mCamYAxis;
	glm::vec3 mCamXAxis;
	glm::vec3 mCamZAxis;
	float	  mCollisionRadius;
	bool	  mDestroyed;

	// drawing buffers. each subclass has a set of these buffers which contain the modelspace coordinates of the vertices. 
	std::vector<glm::vec3> vArray;
	
    // Makes the model follow a path defined by a set of waypoints
    Path* mPath;
	BSpline* mSpline;
	float mSplineParameterT;
    float mSpeed;
    unsigned int mTargetWaypoint;

	// Material Constants
	float ka;
	float kd;
	float ks;
	float n;
};
