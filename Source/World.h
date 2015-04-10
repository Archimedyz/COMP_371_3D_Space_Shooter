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
#include <time.h>
#include <glm/glm.hpp>

class Camera;
class Model;
class Path;
class BSpline;

class World
{
public:
	World();
	~World();
	
    static World* GetInstance();
	static int addCounter;

	void Update(float dt);
	void Draw();

	void LoadScene(const char * scene_path);
    void LoadCameras();

    Path* FindPath(ci_string pathName);
    BSpline* FindSpline(ci_string pathName);
    BSpline* FindSplineByIndex(unsigned int index);
    Model* FindModelByIndex(unsigned int index);
	Model* GetPlayer() { return player; }

	void AddModel(Model*);

private:
    static World* instance;

	Model* player;
	std::vector<Model*> mModel;
    std::vector<Path*> mPath;
    std::vector<BSpline*> mSpline;
	std::vector<Camera*> mCamera;
	unsigned int mCurrentCamera;

	clock_t Clock;

	bool isParallel(glm::vec3 v1, glm::vec3 v2);
};
